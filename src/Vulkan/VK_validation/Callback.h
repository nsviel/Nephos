#pragma once

#include <Vulkan/VK_validation/Log/LOG_debug.h>
#include <Vulkan/VK_validation/Log/LOG_shader.h>
#include <cstring>


namespace vk::validation{

//Validation layer callback function
static VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,VkDebugUtilsMessageTypeFlagsEXT message_type,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData){
  std::string message(pCallbackData->pMessage);
  //---------------------------

  //Shader printf
  size_t shaderPos = message.find("[SHADER]");
  if(shaderPos != std::string::npos){
    LOG_shader::get_instance().add_shader_printf(message);
  }
  //Common validation layer message
  else if(message_type == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT){
    LOG_debug::get_instance().print_validation_error(message);
  }

  //---------------------------
  return VK_FALSE;
}

}
