set(LIBRARY_NAME SENSOR_REALSENSE)

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
find_package(realsense2 REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  MAIN_CORE
  MAIN_UTILITY
  DYNAMIC_SENSOR

  ${realsense2_LIBRARY}
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
