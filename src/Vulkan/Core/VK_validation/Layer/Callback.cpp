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
  message.text = std::string(callback_data->pMessage);
  message.name = std::string(callback_data->pMessageIdName);
  message.ID = callback_data->messageIdNumber;
  message.severity = find_severity(severity);
  message.type = find_type(type);
  message.log = find_log(message);
  message.user_data = user_data;

  //Print message according to log type
  switch(message.log){
    case vk::validation::DEBUG:{
      vk::validation::log::Debug vk_debug;
      vk_debug.print_message(message);
      break;
    }
    case vk::validation::VERBOSE:{
      break;
    }
    case vk::validation::SHADER:{
      vk::validation::log::Shader vk_shader;
      //vk_shader.print_message(message.text);
      break;
    }
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
vk::validation::Log find_log(vk::validation::Message& message){
  vk::validation::Log log = vk::validation::DEBUG;
  //---------------------------

  //Info stuff
  if(message.severity == "info" || message.severity == "verbose"){
    log = vk::validation::VERBOSE;
  }
  //Shader
  else if(message.text.find("[SHADER]") != std::string::npos){
    log = vk::validation::SHADER;
  }

  //---------------------------
  return log;
}

}
