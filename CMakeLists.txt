cmake_minimum_required(VERSION 3.22)
project(HWAL)

include(cmake/subdirlist.cmake)

set(DIRS 2022)
foreach(DIR ${DIRS})
  add_subdirectory(${DIR})
endforeach()
