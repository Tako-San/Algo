SUBDIRLIST(DIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(DIR ${DIRS})
  add_subdirectory(${DIR})
endforeach()
