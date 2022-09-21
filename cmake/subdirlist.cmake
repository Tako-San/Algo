
macro(SUBDIRLIST result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

macro(hwal_add_task TASKNAME)
  add_executable(${TASKNAME} ${TASKNAME}.cc)

  target_compile_options(${TASKNAME} PRIVATE -Wall -Wextra -Wpedantic -O2)
  target_compile_features(${TASKNAME} PRIVATE cxx_std_20)

  set_target_properties(${TASKNAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
  )
endmacro()
