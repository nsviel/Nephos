set(LIBRARY_NAME LIBRARY_OPERATION)

#-----------------
# Source files
#-----------------

file(GLOB_RECURSE ALL_SOURCES
  *.cpp
  *.h
)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})
find_package( OpenCV REQUIRED )

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_UTILITY
  LIBRARY_KINECT

  ${OpenCV_LIBS}
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
