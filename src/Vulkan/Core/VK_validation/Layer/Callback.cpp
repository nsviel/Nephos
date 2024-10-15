#include "Callback.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <cstring>


namespace vk::validation{

//Validation layer callback function
VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data){
  //---------------------------

  //Retrieve and store message elements
  vk::validation::Message message;
  message.texte = std::string(callback_data->pMessage);
  message.name = std::string(callback_data->pMessageIdName);
  message.ID = callback_data->messageIdNumber;
  message.severity = severity;
  message.type = type;
  message.user_data = user_data;


/*
  //Shader printf
  size_t shaderPos = message.find("[SHADER]");
  if(shaderPos != std::string::npos){
    vk::validation::log::Shader::get_instance().print_message(message);
  }
  //Common validation layer message
  else if(message_type == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT){
    vk::validation::log::Debug::get_instance().print_message(message);
  }*/

  //---------------------------
  return VK_FALSE;
}

}
VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type, const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data){
  std::string message(callback_data->pMessage);
  //---------------------------


  //---------------------------
  return VK_FALSE;
}
