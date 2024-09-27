#include "Callback.h"

#include <Vulkan/Core/VK_validation/Log/Debug.h>
#include <Vulkan/Core/VK_validation/Log/Shader.h>
#include <Utility/Namespace.h>
#include <cstring>


namespace vk::validation{

//Validation layer callback function
VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData){
  std::string message(pCallbackData->pMessage);
  //---------------------------

  //Shader printf
  size_t shaderPos = message.find("[SHADER]");
  if(shaderPos != std::string::npos){
    vk::validation::log::Shader::get_instance().print_message(message);
  }
  //Common validation layer message
  else if(message_type == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT){
    vk::validation::log::Debug::get_instance().print_message(message);
  }

  //---------------------------
  return VK_FALSE;
}

}
