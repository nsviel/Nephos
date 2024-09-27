#pragma once

#include <vulkan/vulkan.h>
#include <cstring>


namespace vk::validation{

//Validation layer callback function
VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

}
