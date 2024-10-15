#include "Callback.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <cstring>


namespace vk::validation{

//Main function
VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data){
  //---------------------------

  //Retrieve and store message elements
  vk::validation::Message message;
  message.texte = std::string(callback_data->pMessage);
  message.name = std::string(callback_data->pMessageIdName);
  message.ID = callback_data->messageIdNumber;
  message.severity = find_severity(severity);
  message.type = find_type(type);
  message.user_data = user_data;

  //Shader printf
  size_t shaderPos = message.texte.find("[SHADER]");
  if(shaderPos != std::string::npos){
    vk::validation::log::Shader vk_shader;
    vk_shader.print_message(message.texte);
  }
  //Common validation layer message
  else if(type == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT){
    vk::validation::log::Debug vk_debug;
    vk_debug.print_message(message.texte);
  }

  //---------------------------
  return VK_FALSE;
}

//Subfunction
std::string find_severity(VkDebugUtilsMessageSeverityFlagBitsEXT severity){
  std::string str = "";
  //---------------------------

  switch(severity){
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:{
      str = "verbose";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:{
      str = "info";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:{
      str = "warning";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:{
      str = "error";
      break;
    }
  }

  //---------------------------
  return str;
}
std::string find_type(VkDebugUtilsMessageTypeFlagsEXT type){
  std::string str = "";
  //---------------------------

  switch(type){
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:{
      str = "general";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:{
      str = "validation";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:{
      str = "performance";
      break;
    }
  }

  //---------------------------
  return str;
}

}
