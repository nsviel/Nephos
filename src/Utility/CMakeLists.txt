set(LIBRARY_NAME MAIN_UTILITY)

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
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(spdlog REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  MAIN_EXTERN

  Eigen3::Eigen # Eigen
  spdlog::spdlog_header_only
  -lstdc++fs    # std::experimental::filesystem
  #-lnvidia-ml   # Nvidia GPU stuff
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
