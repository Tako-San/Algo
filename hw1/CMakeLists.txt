cmake_minimum_required(VERSION 3.10)

project(HW)

set(TASKS 1_authomata 2_symdiff 3_intersection 4_sequence 5_permutation)

include(warns.cmake)

foreach(TASK ${TASKS})
  add_executable(${TASK} ${TASK}.cc)
  target_compile_options(${TASK} PRIVATE ${DED_GCC_WARNS})
  target_compile_options(${TASK} PRIVATE ${DED_SAN})
  target_link_options(${TASK} PRIVATE ${DED_SAN})
endforeach()
