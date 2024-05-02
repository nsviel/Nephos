set(LIBRARY_NAME LIBRARY_ENGINE)

#-----------------
# Source files
#-----------------
add_subdirectory(Camera)
add_subdirectory(Operation)
add_subdirectory(Render)
add_subdirectory(Scene)
add_subdirectory(Loader)
add_subdirectory(Data)
add_subdirectory(Dynamic)

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
  LIBRARY_CAPTURE
  LIBRARY_CAMERA
  LIBRARY_OPERATION
  LIBRARY_MODULE
  LIBRARY_RENDERING
  LIBRARY_SCENE
  LIBRARY_DYNAMIC
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
