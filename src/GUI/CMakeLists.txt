set(LIBRARY_NAME LIBRARY_GUI)

#-----------------
# Source files
#-----------------
add_subdirectory(TAB_dev)
add_subdirectory(TAB_render)
add_subdirectory(GUI_element)
add_subdirectory(GUI_ressource)

file(GLOB_RECURSE ALL_SOURCES
  GUI_element/*.cpp
  GUI.cpp
)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_GUI_TAB_DEV
  LIBRARY_GUI_TAB_RENDER
  LIBRARY_GUI_ELEMENT
  LIBRARY_GUI_RESSOURCE
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
