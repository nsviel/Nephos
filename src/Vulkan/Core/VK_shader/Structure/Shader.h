#pragma once

#include <Vulkan/Core/VK_shader/Structure/Info.h>
#include <Vulkan/Core/VK_shader/Structure/Module.h>


namespace vk::shader::structure{

struct Shader{
  //---------------------------

  vk::shader::structure::Info info;
  vk::shader::structure::Module module;

  //---------------------------
};

}
