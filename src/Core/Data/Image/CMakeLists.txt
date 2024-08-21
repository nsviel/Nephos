set(LIBRARY_NAME DATA_IMAGE)

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
find_package(OpenCV REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  MAIN_UTILITY
  CORE_DATA

  ${OpenCV_LIBS}
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
