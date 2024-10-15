#pragma once

#include <Vulkan/Core/VK_shader/Structure/Info.h>
#include <Vulkan/Core/VK_shader/Structure/Module.h>
#include <string>


namespace vk::validation{

struct Message{
  //---------------------------

  vk::validation::Log log = vk::validation::DEBUG;
  std::string text = "";
  std::string name = "";
  std::string type = "";
  std::string severity = "";
  uint32_t ID;
  void* user_data;

  //---------------------------
};

}
