set(LIBRARY_NAME LIBRARY_CORE)

#-----------------
# Source files
#-----------------
add_subdirectory(Engine)
add_subdirectory(IO)
add_subdirectory(Data)
add_subdirectory(Profiler)
add_subdirectory(Control)

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
  ENGINE_CAMERA
  CORE_IO
  LIBRARY_OPERATION
  ENGINE_RENDERER
  LIBRARY_DYNAMIC
  LIBRARY_CONTROL
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
