cmake_minimum_required(VERSION 3.10)

project(HW)

set(TASKS 1_authomata 2_symdiff 3_intersection 4_sequence 5_permutation)

foreach(TASK ${TASKS})
  add_executable(${TASK} ${TASK}.cc)
  target_compile_options(${TASK} PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(${TASK} PRIVATE -fsanitize=address,undefined)
  target_link_options(${TASK} PRIVATE -fsanitize=address,undefined)
endforeach()
