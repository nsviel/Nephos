set(LIBRARY_NAME CORE_SYSTEM)

#-----------------
# Source files
#-----------------
add_subdirectory(Hardware)
add_subdirectory(Network)
add_subdirectory(Profiler)
add_subdirectory(Thread)
add_subdirectory(Timer)

file(GLOB_RECURSE ALL_SOURCES
  Node.cpp
)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  CORE_UTILITY

  SYSTEM_PROFILER
  SYSTEM_HARDWARE
  SYSTEM_NETWORK
  SYSTEM_THREAD
  SYSTEM_TIMER
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)
