set(LIBRARY_NAME LIBRARY_ENGINE)

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
find_package(Vulkan REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN
  LIBRARY_UTILITY
  LIBRARY_VULKAN

  ${Vulkan_LIBRARIES}

  Eigen3::Eigen # Eigen
  tins          # Sniffer
  -lavformat    # ffmpeg
  -lavdevice    # ffmpeg
  -lavcodec     # ffmpeg
  -lswresample  # ffmpeg
  -lswscale     # ffmpeg
  -lavutil      # ffmpeg
  -lturbojpeg
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
