set(LIBRARY_NAME LIBRARY_MODULE)

#-----------------
# Source files
#-----------------
add_subdirectory(Radiometry)
add_subdirectory(Registration)
add_subdirectory(Rendering)

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
  LIBRARY_EXTERN
  LIBRARY_UTILITY
  LIBRARY_VULKAN
  LIBRARY_ENGINE
  LIBRARY_RENDERING
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
