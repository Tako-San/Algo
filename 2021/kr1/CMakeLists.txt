cmake_minimum_required(VERSION 3.10)

project(HW)

set(TASKS 1_battle 2_subarrays 3_positivism 4_find_num)

foreach(TASK ${TASKS})
  add_executable(${TASK} ${TASK}.cc)
  target_compile_options(${TASK} PRIVATE -Wall -Wextra)
  target_compile_features(${TASK} PRIVATE cxx_std_20)
endforeach()
