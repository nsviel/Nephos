set(LIBRARY_NAME LIBRARY_GUI_RENDER)

#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES *.cpp)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN
  LIBRARY_RESSOURCE
  LIBRARY_ENGINE
  LIBRARY_GUI

  Eigen3::Eigen # Eigen
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
