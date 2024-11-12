#include <pybind11/pybind11.h>
#include "../src/app.h"  // Include the main.cpp file to access run_vulkan_engine()

namespace py = pybind11;

PYBIND11_MODULE(pynephos, m) {
    m.doc() = "Vulkan Engine Python Bindings";  // Optional: module docstring

    // Bind the run_vulkan_engine function
    m.def("run", &run, "Run the Vulkan engine from Python");
}
