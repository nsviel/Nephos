set(LIBRARY_NAME LIBRARY_DEV)

#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES
  *.cpp
)

add_library(${LIBRARY_NAME} STATIC
  ${ALL_SOURCES}
)

#-----------------
# Dependencies
#-----------------
find_package(Python REQUIRED COMPONENTS Interpreter Development)

include_directories(${Python_INCLUDE_DIRS})

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_UTILITY

  ${Python_LIBRARIES}

  Python::Python
  python3.10
  -lpython3.10
)

#-----------------
# Compilation
#-----------------
target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  ${Python_LIBRARY_DIRS}
  ${PYTHON_INCLUDE_DIRS}
)
