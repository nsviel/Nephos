set(PACKAGE_NAME pynephos)

#-----------------
# Python binding
#-----------------
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

pybind11_add_module(${PACKAGE_NAME}
  ../../src/Application/Interface/App.cpp
  binding.cpp
)

set_target_properties(${PACKAGE_NAME} PROPERTIES
  LIBRARY_OUTPUT_NAME "pynephos"
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pynephos
)

target_link_libraries(${PACKAGE_NAME}
  PRIVATE MAIN_APPLICATION
)
file(COPY ${CMAKE_SOURCE_DIR}/shader/ DESTINATION ${CMAKE_BINARY_DIR}/pynephos/shader)
file(COPY ${CMAKE_SOURCE_DIR}/media/ DESTINATION ${CMAKE_BINARY_DIR}/pynephos/media)
file(WRITE ${CMAKE_BINARY_DIR}/pynephos/__init__.py "")
