#pragma once

#include <vulkan/vulkan.h>


class LOG_debug
{
public:
  static LOG_debug& get_instance(){
    static LOG_debug instance;
    return instance;
  }

  //Main function
  void validation_message(const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

private:
  LOG_debug() = default;
};
