set(LIBRARY_NAME LIBRARY_GUI)

#-----------------
# Source files
#-----------------
add_subdirectory(TAB_dev)
add_subdirectory(TAB_render)
add_subdirectory(GUI_element)
add_subdirectory(GUI_ressource)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC
  GUI.cpp
)

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN
  LIBRARY_RESSOURCE
  LIBRARY_ENGINE

  LIBRARY_GUI_ELEMENT
  LIBRARY_GUI_RESSOURCE
  LIBRARY_GUI_TAB_DEV
  LIBRARY_GUI_TAB_RENDER
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
