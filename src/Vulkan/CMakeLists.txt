set(LIBRARY_NAME MAIN_VULKAN)

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
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

#find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
#find_package(pybind11 REQUIRED)
#pybind11_add_module(vulkan_engine ${ALL_SOURCES})

target_link_libraries(${LIBRARY_NAME} PUBLIC
  MAIN_EXTERN
  MAIN_UTILITY

  #Python3::Python

  ${Vulkan_LIBRARIES}
  -lglfw        # glfw
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)
