set(LIBRARY_NAME LIBRARY_APPLICATION)

#-----------------
# Source files
#-----------------
add_subdirectory(GUI)
add_subdirectory(Scene)

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
  LIBRARY_ENGINE
  LIBRARY_GUI
  LIBRARY_SCENE
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
