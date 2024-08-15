set(LIBRARY_NAME MAIN_CORE)

#-----------------
# Source files
#-----------------
add_subdirectory(Data)
add_subdirectory(Engine)
add_subdirectory(IO)
add_subdirectory(Profiler)

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
  LIBRARY_UTILITY
  LIBRARY_VULKAN

  CORE_DATA
  CORE_IO
  CORE_ENGINE
  LIBRARY_OPERATION
  LIBRARY_DYNAMIC
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
