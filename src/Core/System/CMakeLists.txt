set(LIBRARY_NAME CORE_SYSTEM)

#-----------------
# Source files
#-----------------
add_subdirectory(Profiler)

file(GLOB_RECURSE ALL_SOURCES
  Hardware/*.cpp
  Network/*.cpp
  Thread/*.cpp
  Timer/*.cpp
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
  MAIN_EXTERN
  MAIN_UTILITY
  CORE_PROFILER

  Eigen3::Eigen # Eigen
  -lgit2        # git
  -lstdc++fs    # std::experimental::filesystem
  -lnvidia-ml   # Nvidia GPU stuff
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)
