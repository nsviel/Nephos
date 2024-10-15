#pragma once

#include <vulkan/vulkan.h>
#include <cstring>


namespace vk::validation{

//Validation layer callback function
VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data);

}
