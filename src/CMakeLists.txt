set(EXECUTABLE_NAME executable)

#-----------------
# Source files
#-----------------
add_subdirectory(Application)
add_subdirectory(Utility)
add_subdirectory(Engine)
add_subdirectory(GUI)
add_subdirectory(Dev)
add_subdirectory(Vulkan)

#-----------------
# Compilation
#-----------------
add_executable(executable
  main.cpp
)

#-----------------
# Dependencies
#-----------------
target_link_libraries(${EXECUTABLE_NAME}
  LIBRARY_APPLICATION
  LIBRARY_ENGINE
  LIBRARY_GUI
  LIBRARY_UTILITY
  LIBRARY_DEV
  LIBRARY_VULKAN
)
