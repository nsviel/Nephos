set(LIBRARY_NAME LIBRARY_ENGINE)

#-----------------
# Source files
#-----------------
add_subdirectory(Camera)
add_subdirectory(Operation)
add_subdirectory(Glyph)
add_subdirectory(Render)
add_subdirectory(Scene)
add_subdirectory(Loader)
add_subdirectory(Data)

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
find_package(Vulkan REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

find_package(Matroska REQUIRED)
find_package(EBML REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_UTILITY
  LIBRARY_VULKAN
  LIBRARY_CAPTURE
  LIBRARY_CAMERA
  LIBRARY_OPERATION
  LIBRARY_MODULE
  LIBRARY_RENDERING
  LIBRARY_SCENE

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
