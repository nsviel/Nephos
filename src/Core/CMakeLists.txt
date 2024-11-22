set(LIBRARY_NAME MAIN_CORE)

#-----------------
# Source files
#-----------------
add_subdirectory(Data)
add_subdirectory(Engine)
add_subdirectory(IO)
add_subdirectory(Operation)
add_subdirectory(System)

file(GLOB_RECURSE ALL_SOURCES
  Node.cpp
)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
target_link_libraries(${LIBRARY_NAME} PUBLIC
  MAIN_UTILITY
  MAIN_VULKAN

  CORE_DATA
  CORE_ENGINE
  CORE_IO
  CORE_SYSTEM
  CORE_OPERATION
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>   # include module directory
)
