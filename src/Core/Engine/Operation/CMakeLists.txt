set(LIBRARY_NAME ENGINE_OPERATION)

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
find_package(OpenCV REQUIRED)
find_library(LZ4_LIBRARIES NAMES liblz4.so HINTS "lz4/lib")

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_UTILITY
  MAIN_CORE

  ${OpenCV_LIBS}
  ${LZ4_LIBRARIES}
  flann
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
