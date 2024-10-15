#pragma once

#include <Vulkan/Core/VK_shader/Structure/Info.h>
#include <Vulkan/Core/VK_shader/Structure/Module.h>
#include <string>


namespace vk::validation{

struct Message{
  //---------------------------

  std::string texte = "";
  std::string name = "";
  uint32_t ID;
  VkDebugUtilsMessageSeverityFlagBitsEXT severity;
  VkDebugUtilsMessageTypeFlagsEXT type;
  void* user_data;

  //---------------------------
};

}
