set(LIBRARY_NAME CORE_SYSTEM)

#-----------------
# Source files
#-----------------
add_subdirectory(Thread)
add_subdirectory(USB)

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
find_package(HDF5 REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  MAIN_UTILITY

  SYSTEM_THREAD
  SYSTEM_USB
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
