set(LIBRARY_NAME MAIN_DYNAMIC)

#-----------------
# Source files
#-----------------
add_subdirectory(Sensor)
add_subdirectory(Processing)

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
  MAIN_UTILITY

  DYNAMIC_PROCESSING
  DYNAMIC_SENSOR
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
