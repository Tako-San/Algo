#include <coroutine>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <unordered_map>

namespace CoroBoilerplate
{

struct ResumableNoInc
{
  struct promise_type
  {
    using CoroHandle = std::coroutine_handle<promise_type>;
    auto get_return_object() { return CoroHandle::from_promise(*this); }
    auto initial_suspend() noexcept { return std::suspend_always{}; }
    auto final_suspend() noexcept { return std::suspend_always{}; }
    void unhandled_exception() { std::terminate(); }
    void return_void() {}
  };

  using CoroHandle = std::coroutine_handle<promise_type>;

  ResumableNoInc(CoroHandle handle) : handle_(handle) {}
  ResumableNoInc(const ResumableNoInc &) = delete;
  ResumableNoInc(ResumableNoInc &&rhs) : handle_(rhs.handle_)
  {
    rhs.handle_ = nullptr;
  }
  ~ResumableNoInc()
  {
    if (handle_)
      handle_.destroy();
  }

  bool resume()
  {
    if (!handle_.done())
      handle_.resume();
    return !handle_.done();
  }

  CoroHandle handle()
  {
    auto h = handle_;
    handle_ = nullptr;
    return h;
  }

private:
  CoroHandle handle_;
};

template <typename T>
struct Generator
{
  struct promise_type
  {
    T current_value;
    using CoroHandle = std::coroutine_handle<promise_type>;
    auto get_return_object() { return CoroHandle::from_promise(*this); }
    auto initial_suspend() noexcept { return std::suspend_always{}; }
    auto final_suspend() noexcept { return std::suspend_always{}; }
    void unhandled_exception() { std::terminate(); }
    void return_void() {}
    auto yield_value(T value)
    {
      current_value = value;
      return std::suspend_always{};
    }
  };

  using CoroHandle = std::coroutine_handle<promise_type>;

  Generator(CoroHandle handle) : handle_(handle) {}
  Generator(Generator &&rhs) : handle_(rhs.handle_) { rhs.handle_ = nullptr; }
  Generator(const Generator &) = delete;
  ~Generator()
  {
    if (handle_)
      handle_.destroy();
  }

  bool moveNext()
  {
    if (!handle_)
      return false;

    handle_.resume();
    return !handle_.done();
  }

  T currentValue() const { return handle_.promise().current_value; }

private:
  CoroHandle handle_;
};

} // namespace CoroBoilerplate
using namespace CoroBoilerplate;

namespace STM
{

enum class State : char
{
  Code,
  String,
  Charachter,
  MultiLineComment,
  SignleLineComment
};

enum class Sym : char
{
  DoubleQuoteMark,
  SingleQuoteMark,
  DoubleSlash,
  SlashStar,
  StarSlash,
  NewLine,
  Term,
  Sym
};

using CoroT = std::coroutine_handle<>;
using Token = std::pair<Sym, char>;

template <typename F, typename SM>
struct StmAwaiter : public F
{
  SM &stm_;

  StmAwaiter(F f, SM &stm) : F(f), stm_(stm) {}

  bool await_ready() const noexcept { return false; }
  bool await_resume() noexcept { return (stm_.genVal() == Sym::Term); }
  CoroT await_suspend(CoroT) noexcept
  {
    stm_.genNext();
    auto sym = stm_.genVal();
    auto newState = F::operator()(sym);
    return stm_[newState];
  }
};

class StateMachine
{
  State current_;
  std::unordered_map<State, CoroT> states_;
  Generator<Token> gen_;

public:
  StateMachine(Generator<Token> &&g) : gen_(std::move(g)) {}

  CoroT operator[](State s) { return states_[s]; }
  State current() const { return current_; }

  Sym genVal() const { return gen_.currentValue().first; }
  char genChar() const { return gen_.currentValue().second; }
  Token genTok() const { return gen_.currentValue(); }
  void genNext() { gen_.moveNext(); }

  void run(State initial)
  {
    current_ = initial;
    states_[initial].resume();
  }

  template <typename F>
  void addState(State x, F stf)
  {
    states_[x] = stf(*this).handle();
  }

  template <typename F>
  auto getAwaiter(F transition)
  {
    return StmAwaiter<F, decltype(*this)>{transition, *this};
  }
};

/* input sequence generator */
Generator<Token> lexer(std::string_view s)
{
  for (size_t i = 0, end = s.size(); i < end; ++i)
    if (s[i] == '"')
      co_yield {Sym::DoubleQuoteMark, '"'};
    else if (s[i] == '\'')
      co_yield {Sym::SingleQuoteMark, '\''};
    else if (s[i] == '\n')
      co_yield {Sym::NewLine, '\n'};
    else if (s[i] == '/')
      if (++i == end)
        co_yield {Sym::Sym, s[i]};
      else if (s[i] == '/')
        co_yield {Sym::DoubleSlash, '\0'};
      else if (s[i] == '*')
        co_yield {Sym::SlashStar, '\0'};
      else
      {
        --i;
        co_yield {Sym::Sym, s[i]};
      }
    else if (s[i] == '*')
      if (++i == end)
        co_yield {Sym::Sym, '\0'};
      else if (s[i] == '/')
        co_yield {Sym::StarSlash, ' '};
      else
      {
        --i;
        co_yield {Sym::Sym, s[i]};
      }
    else
      co_yield {Sym::Sym, s[i]};

  for (;;)
    co_yield {Sym::Term, '\0'};
}

std::string forPrint(Token tok)
{
  switch (tok.first)
  {
  case Sym::DoubleSlash:
    return "//";
  case Sym::SlashStar:
    return "/*";
  case Sym::StarSlash:
    return "*/";
  default:
    return {tok.second};
  }
}

/* All possible states */

ResumableNoInc StateCode(StateMachine &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::SlashStar)
      return State::MultiLineComment;
    else if (sym == Sym::DoubleSlash)
      return State::SignleLineComment;
    else if (sym == Sym::DoubleQuoteMark)
      return State::String;
    else if (sym == Sym::SingleQuoteMark)
      return State::Charachter;
    return State::Code;
  };

  for (;;)
  {
    bool finish = co_await stm.getAwaiter(transition);
    if (finish)
      break;
    std::cout << stm.genChar();
  }
}

ResumableNoInc StateString(StateMachine &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::DoubleQuoteMark)
      return State::Code;
    return State::String;
  };

  for (;;)
  {
    std::cout << forPrint(stm.genTok());
    bool finish = co_await stm.getAwaiter(transition);
    if (finish)
      break;
  }
}

ResumableNoInc StateChar(StateMachine &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::SingleQuoteMark)
      return State::Code;
    return State::Charachter;
  };

  for (;;)
  {
    std::cout << forPrint(stm.genTok());
    bool finish = co_await stm.getAwaiter(transition);
    if (finish)
      break;
  }
}

ResumableNoInc StateSingleLineComment(StateMachine &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::NewLine)
      return State::Code;
    return State::SignleLineComment;
  };

  for (;;)
    if (auto finish = co_await stm.getAwaiter(transition); finish)
      break;
}

ResumableNoInc StateMultiLineComment(StateMachine &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::StarSlash)
      return State::Code;
    return State::MultiLineComment;
  };

  for (;;)
    if (auto finish = co_await stm.getAwaiter(transition); finish)
      break;
}

} // namespace STM
using namespace STM;

int main()
{
  std::cin >> std::noskipws;

  std::istream_iterator<char> it(std::cin);
  std::istream_iterator<char> end;
  std::string input(it, end);

  StateMachine stm{lexer(input)};
  stm.addState(State::Code, StateCode);
  stm.addState(State::String, StateString);
  stm.addState(State::Charachter, StateChar);
  stm.addState(State::MultiLineComment, StateMultiLineComment);
  stm.addState(State::SignleLineComment, StateSingleLineComment);

  stm.run(State::Code);
  return 0;
}
