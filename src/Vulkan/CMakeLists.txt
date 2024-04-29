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
  VK_render/*.cpp
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
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN
  LIBRARY_UTILITY

  ${Vulkan_LIBRARIES}

  -lglfw        # glfw
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)
