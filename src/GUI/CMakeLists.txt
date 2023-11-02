set(LIBRARY_NAME LIBRARY_GUI)

#-----------------
# Source files
#-----------------
add_subdirectory(Dev)
add_subdirectory(Render)

file(GLOB_RECURSE ALL_SOURCES
  Element/*.cpp
  Ressource/*.cpp
  Tab/*.cpp
  GUI.cpp
)

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
  LIBRARY_GUI_DEV
  LIBRARY_GUI_RENDER

  Eigen3::Eigen #Eigen
 -lavformat     #ffmpeg
 -lavcodec      #ffmpeg
 -lswresample   #ffmpeg
 -lswscale      #ffmpeg
 -lavutil       #ffmpeg
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
