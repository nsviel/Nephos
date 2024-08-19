set(LIBRARY_NAME MODULE_RADIOMETRY)

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
find_package(Python REQUIRED COMPONENTS Interpreter Development)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  CORE_UTILITY
  MAIN_CORE
  CORE_IO

  ${Python_LIBRARIES}
  Python::Python
  python3.10
  -lpython3.10
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
