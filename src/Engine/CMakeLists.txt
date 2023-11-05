set(LIBRARY_NAME LIBRARY_ENGINE)

#-----------------
# Source files
#-----------------


file(GLOB_RECURSE ALL_SOURCES
  ENG_camera/*.cpp
  ENG_data/*.cpp
  ENG_gpu/*.cpp
  ENG_operation/*.cpp
  ENG_shader/*.cpp
  ENG_vulkan/*.cpp
  Engine.cpp
  Param.cpp
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
  LIBRARY_ELEMENT
  LIBRARY_VULKAN

  ${Vulkan_LIBRARIES}

  Eigen3::Eigen # Eigen
  tins          # Sniffer
  -lavformat    # ffmpeg
  -lavcodec     # ffmpeg
  -lswresample  # ffmpeg
  -lswscale     # ffmpeg
  -lavutil      # ffmpeg
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
