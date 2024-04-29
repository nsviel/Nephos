set(LIBRARY_NAME LIBRARY_GRAPH)

#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES
  *.cpp
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
  LIBRARY_CAMERA
  LIBRARY_GLYPH
  LIBRARY_LOADER
  LIBRARY_SCENE
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
