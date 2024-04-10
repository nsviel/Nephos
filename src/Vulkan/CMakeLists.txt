set(LIBRARY_NAME LIBRARY_VULKAN)

#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES
  VK_binding/*.cpp
  VK_command/*.cpp
  VK_data/*.cpp
  VK_device/*.cpp
  VK_drawing/*.cpp
  VK_image/*.cpp
  VK_instance/*.cpp
  VK_main/*.cpp
  VK_presentation/*.cpp
  VK_renderpass/*.cpp
  VK_shader/*.cpp
  VK_struct/*.cpp
  VK_validation/*.cpp
  VK_synchronization/*.cpp
  VK_rendering/*.cpp
  VK_queue/*.cpp
  VK_memory/*.cpp
  VK_pool/*.cpp
  VK_gui/*.cpp
  VK_window/*.cpp
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

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN
  LIBRARY_UTILITY
  LIBRARY_ENGINE

  ${Vulkan_LIBRARIES}

  Eigen3::Eigen # Eigen
  tins          # Sniffer
  -lavformat    # ffmpeg
  -lavdevice    # ffmpeg
  -lavcodec     # ffmpeg
  -lswresample  # ffmpeg
  -lswscale     # ffmpeg
  -lavutil      # ffmpeg
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)
