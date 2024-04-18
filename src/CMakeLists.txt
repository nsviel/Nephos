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
add_subdirectory(Profiler)

#-----------------
# Compilation
#-----------------
add_executable(${EXECUTABLE_NAME}
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
  LIBRARY_PROFILER
)
