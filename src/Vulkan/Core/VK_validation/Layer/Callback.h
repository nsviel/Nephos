#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::validation{

//Main function
VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data);

//Subfunction
std::string find_severity(VkDebugUtilsMessageSeverityFlagBitsEXT severity);
std::string find_type(VkDebugUtilsMessageTypeFlagsEXT type);

}
