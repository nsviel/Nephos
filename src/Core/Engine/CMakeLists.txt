set(LIBRARY_NAME CORE_ENGINE)

#-----------------
# Source files
#-----------------
add_subdirectory(Camera)
add_subdirectory(Renderer)
add_subdirectory(Control)
add_subdirectory(Transformation)

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
  LIBRARY_OPERATION
  LIBRARY_DYNAMIC

  ENGINE_CAMERA
  ENGINE_RENDERER
  ENGINE_CONTROL
  ENGINE_TRANSFORMATION
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
