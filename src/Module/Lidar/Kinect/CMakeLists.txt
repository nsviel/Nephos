set(LIBRARY_NAME LIBRARY_KINECT)

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

#-----------------
# Dependencies
#-----------------
find_package(Python REQUIRED COMPONENTS Interpreter Development)
find_package(k4a REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_UTILITY
  LIBRARY_ENGINE
  LIBRARY_RADIOMETRY

  ${Python_LIBRARIES}
  ${k4a_LIBS}

  Python::Python
  python3.10
  -lpython3.10
  -lturbojpeg   # Convertion JPEG -> BRGA
  -lk4a
  -lk4arecord
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
