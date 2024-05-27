#pragma once

#include <Utility/Specific/Common.h>
#include "LOG_shader.h"
#include "LOG_debug.h"


namespace vk::validation{

//Validation layer callback function
static VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,VkDebugUtilsMessageTypeFlagsEXT message_type,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData){
  //---------------------------

  //Shader printf
  const char* shaderPos = std::strstr(pCallbackData->pMessage, "[SHADER]");
  if (shaderPos != nullptr){
    const char* message = shaderPos + std::strlen("[SHADER]");
    LOG_shader::get_instance().add_shader_printf(message);
  }
  //Common validation layer message
  else if(message_type == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT){
    LOG_debug::get_instance().validation_message(pCallbackData);
  }

  //---------------------------
  return VK_FALSE;
}

}
