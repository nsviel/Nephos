set(LIBRARY_NAME LIBRARY_MODULE)

#-----------------
# Source files
#-----------------
add_subdirectory(Operation)
add_subdirectory(Radiometry)
#add_subdirectory(Registration)

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
  LIBRARY_CORE
  LIBRARY_SCENE
  LIBRARY_REALSENSE
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
