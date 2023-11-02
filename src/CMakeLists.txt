#-----------------
# Source files
#-----------------
add_subdirectory(Application)
add_subdirectory(Ressource)
add_subdirectory(Engine)
add_subdirectory(GUI)

file(GLOB_RECURSE ALL_SOURCES
  Application/*.cpp
  config.h
  main.cpp
)

# Executable
add_executable(executable
  ${ALL_SOURCES}
)

#-----------------
# Dependencies
#-----------------
find_package(Python REQUIRED COMPONENTS Interpreter Development)

include_directories(${Python_INCLUDE_DIRS})

target_link_libraries(executable
  LIBRARY_APPLICATION
  LIBRARY_EXTERN
  LIBRARY_RESSOURCE
  LIBRARY_ENGINE
  LIBRARY_GUI

  ${Python_LIBRARIES}
  Python::Python
  python3.10
  -lpython3.10

  #FFMPEG
 -lavformat
 -lavcodec
 -lswresample
 -lswscale
 -lavutil
)

target_sources(executable PRIVATE
  ${EXTERN_TRG_SRC}
)

#-----------------
# Compilation
#-----------------
target_include_directories(executable PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/extern"

  ${Python_LIBRARY_DIRS}
  ${PYTHON_INCLUDE_DIRS}
)
