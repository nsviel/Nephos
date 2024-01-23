set(LIBRARY_NAME LIBRARY_ENGINE)

#-----------------
# Source files
#-----------------
add_subdirectory(Capture/K4N)

file(GLOB_RECURSE ALL_SOURCES
  Camera/*.cpp
  Capture/Node.cpp
  Operation/*.cpp
  Render/*.cpp
  Data/*.cpp
  Shader/*.cpp
  Engine.cpp
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

find_package(Matroska REQUIRED)
find_package(EBML REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN
  LIBRARY_UTILITY
  LIBRARY_VULKAN
  LIBRARY_K4N
  LIBRARY_GUI

  Eigen3::Eigen # Eigen
  tins          # Sniffer
  -lavformat    # ffmpeg
  -lavdevice    # ffmpeg
  -lavcodec     # ffmpeg
  -lswresample  # ffmpeg
  -lswscale     # ffmpeg
  -lavutil      # ffmpeg
  -lturbojpeg   # Convertion JPEG -> BRGA
  -lebml
  -lmatroska
  -lebml
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
