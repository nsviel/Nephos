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
target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN
  LIBRARY_RESSOURCE
  LIBRARY_ENGINE
  LIBRARY_GUI
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
