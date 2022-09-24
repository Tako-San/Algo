#include <coroutine>
#include <iostream>
#include <string>
#include <unordered_map>

struct ResumableNoInc
{
  struct promise_type
  {
    using coro_handle = std::coroutine_handle<promise_type>;
    auto get_return_object() { return coro_handle::from_promise(*this); }
    auto initial_suspend() noexcept { return std::suspend_always{}; }
    auto final_suspend() noexcept { return std::suspend_always{}; }
    void unhandled_exception() { std::terminate(); }
    void return_void() {}
  };

  using coro_handle = std::coroutine_handle<promise_type>;

  ResumableNoInc(coro_handle handle) : handle_(handle) {}
  ResumableNoInc(ResumableNoInc &&rhs) : handle_(rhs.handle_)
  {
    rhs.handle_ = nullptr;
  }
  ResumableNoInc(const ResumableNoInc &) = delete;
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

  coro_handle handle()
  {
    auto h = handle_;
    handle_ = nullptr;
    return h;
  }

private:
  coro_handle handle_;
};

template <typename T>
struct Generator
{
  struct promise_type
  {
    T current_value;
    using coro_handle = std::coroutine_handle<promise_type>;
    auto get_return_object() { return coro_handle::from_promise(*this); }
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

  using coro_handle = std::coroutine_handle<promise_type>;

  Generator(coro_handle handle) : handle_(handle) {}
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
  coro_handle handle_;
};

enum class State : char
{
  Code,
  String,
  MultiLineComment,
  SignleLineComment
};

enum class Sym : char
{
  DoubleSlash,
  SlashStar,
  StarSlash,
  QuoteMark,
  NewLine,
  Term,
  Sym
};

using CoroT = std::coroutine_handle<>;

template <typename F, typename SM>
struct StmAwaiter : public F
{
  SM &stm_;

  StmAwaiter(F f, SM &stm) : F(f), stm_(stm) {}

  bool await_ready() const noexcept { return false; }

  CoroT await_suspend(CoroT) noexcept
  {
    stm_.genNext();
    auto sym = stm_.genVal();
    auto newState = F::operator()(sym);
    return stm_[newState];
  }

  bool await_resume() noexcept { return (stm_.genVal() == Sym::Term); }
};

template <typename State, typename Sym>
class StateMachine
{
  State current_;
  std::unordered_map<State, CoroT> states_;
  Generator<Sym> gen_;

public:
  StateMachine(Generator<Sym> &&g) : gen_(std::move(g)) {}

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

  CoroT operator[](State s) { return states_[s]; }

  State current() const { return current_; }

  template <typename F>
  auto getAwaiter(F transition)
  {
    return StmAwaiter<F, decltype(*this)>{transition, *this};
  }

  Sym genVal() const { return gen_.currentValue(); }

  void genNext() { gen_.moveNext(); }
};

using StateMT = StateMachine<State, Sym>;

Generator<Sym> inputSeq(std::string s)
{
  for (size_t i = 0, end = s.size(); i < end; ++i)
    switch (s[i])
    {
    case '"':
      co_yield Sym::QuoteMark;
      break;

    case '/': {
      auto res = Sym::Sym;
      if (i + 1 == end)
        res = Sym::Sym;
      switch (s[++i])
      {
      case '/':
        res = Sym::DoubleSlash;
        break;
      case '*':
        res = Sym::SlashStar;
        break;
      default:
        --i;
        res = Sym::Sym;
        break;
      }
      co_yield res;
    }
    break;

    case '*': {
      auto res = Sym::Sym;
      if (i + 1 == end)
        res = Sym::Sym;
      if (s[++i] == '/')
        res = Sym::StarSlash;
      else
        --i, res = Sym::Sym;

      co_yield res;
    }
    break;

    case '\n':
      co_yield Sym::NewLine;
      break;

    default:
      co_yield Sym::Sym;
      break;
    }

  for (;;)
    co_yield Sym::Term;
}

ResumableNoInc StateCode(StateMT &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::SlashStar)
      return State::MultiLineComment;
    else if (sym == Sym::DoubleSlash)
      return State::SignleLineComment;
    else if (sym == Sym::QuoteMark)
      return State::String;
    return State::Code;
  };

  for (;;)
  {
    std::cout << "Code" << std::endl;
    bool finish = co_await stm.getAwaiter(transition);
    if (finish)
      break;
  }
}

ResumableNoInc StateString(StateMT &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::QuoteMark)
      return State::Code;
    return State::String;
  };

  for (;;)
  {
    std::cout << "String" << std::endl;
    bool finish = co_await stm.getAwaiter(transition);
    if (finish)
      break;
  }
}

ResumableNoInc StateSingleLineComment(StateMT &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::NewLine)
      return State::Code;
    return State::SignleLineComment;
  };

  for (;;)
  {
    std::cout << "Single line comment" << std::endl;
    bool finish = co_await stm.getAwaiter(transition);
    if (finish)
      break;
  }
}


ResumableNoInc StateMultiLineComment(StateMT &stm)
{
  auto transition = [](auto sym) {
    if (sym == Sym::StarSlash)
      return State::Code;
    return State::MultiLineComment;
  };

  for (;;)
  {
    std::cout << "Multi line comment" << std::endl;
    bool finish = co_await stm.getAwaiter(transition);
    if (finish)
      break;
  }
}

int main()
{
  auto gen = inputSeq("c\"s\"/*hi*/");
  StateMT stm{std::move(gen)};
  stm.addState(State::String, StateString);
  stm.addState(State::Code, StateCode);
  stm.addState(State::MultiLineComment, StateMultiLineComment);
  stm.addState(State::SignleLineComment, StateSingleLineComment);
  stm.run(State::Code);

  std::string st = (stm.current() == State::Code ? "Code" : "Not code");
  std::cout << "State machine in state " << st << std::endl;
  return 0;
}
