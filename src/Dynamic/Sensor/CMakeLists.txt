set(LIBRARY_NAME DYNAMIC_SENSOR)

#-----------------
# Source files
#-----------------
#add_subdirectory(Kinect)
add_subdirectory(RealSense)
add_subdirectory(Velodyne)

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
  MAIN_CORE
  APPLICATION_SCENE
  LIBRARY_REALSENSE
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
