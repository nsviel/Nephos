#ifndef COMMON_H
#define COMMON_H

//Include
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <cstdlib>
#include <stdint.h>
#include <set>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
#include <sys/file.h>
#include <chrono>
#include <array>
#include <vulkan/vulkan.h>
#include <thread>
#include <typeindex>
#include <any>
#include <utility>
#include <functional>

//Namespaces
using namespace std;
using namespace glm;

//Function
#include <UTL_function/fct_terminal.h>
#include <UTL_function/fct_math.h>
#include <UTL_function/fct_chrono.h> //For debuging
#include <UTL_function/fct_timer.h>  //For time profilling

//Data
#include <UTL_base/Struct_object.h>
#include <UTL_base/Struct_set.h>
#include <UTL_base/Struct_data_file.h>
#include <UTL_base/Struct_glyph.h>
#include <UTL_base/data_nsp.h>

//GUI
#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>


#endif
