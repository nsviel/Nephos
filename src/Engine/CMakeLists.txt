set(LIBRARY_NAME LIBRARY_ENGINE)

#-----------------
# Source files
#-----------------
add_subdirectory(Vulkan)

file(GLOB_RECURSE ALL_SOURCES
  Camera/*.cpp
  Data/*.cpp
  GPU/*.cpp
  Operation/*.cpp
  Shader/*.cpp
  #Vulkan/*.cpp
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
  LIBRARY_RESSOURCE
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
