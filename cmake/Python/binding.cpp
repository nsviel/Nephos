#include <pybind11/pybind11.h>
#include <Application/Namespace.h>  // Include the main.cpp file to access run_vulkan_engine()

namespace py = pybind11;

PYBIND11_MODULE(pynephos, m) {
  m.doc() = "Vulkan Engine Python Bindings";  // Optional: module docstring

  py::class_<App>(m, "App")
  .def(py::init<>())  // Bind the constructor of App (assumes default constructor)
  .def("run", &App::run, "Run the Vulkan engine from Python")
  .def("close", &App::close, "Close the Vulkan engine from Python")
  .def("add_cloud", &App::add_cloud, "Add a cloud to the Vulkan engine");
}
