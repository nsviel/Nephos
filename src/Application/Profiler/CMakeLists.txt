set(LIBRARY_NAME APPLICATION_PROFILER)

#-----------------
# Source files
#-----------------
add_subdirectory(Hardware)
add_subdirectory(Monitor)

file(GLOB_RECURSE ALL_SOURCES
  Node.cpp
  gui/*.cpp
)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  MAIN_CORE
  MAIN_UTILITY

  PROFILER_MONITOR
  PROFILER_HARDWARE
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
