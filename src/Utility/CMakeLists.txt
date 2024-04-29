set(LIBRARY_NAME LIBRARY_UTILITY)

#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES
  Base/*.cpp
  Element/*.cpp
  Function/*.cpp
  Specific/*.cpp
  Network/*.cpp
  Node.cpp
)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_CAMERA

  Eigen3::Eigen # Eigen
  -lgit2        # git
  -lstdc++fs    # std::experimental::filesystem
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)
