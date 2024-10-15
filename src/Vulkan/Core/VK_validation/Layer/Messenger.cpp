#include "Messenger.h"

#include <Vulkan/Namespace.h>


namespace vk::validation{

//Constructor / Destructor
Messenger::Messenger(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Messenger::~Messenger(){}

//Main function
void Messenger::create_messenger_info(){
  //---------------------------

  VkDebugUtilsMessengerCreateInfoEXT messenger_info{};
  messenger_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  messenger_info.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
  messenger_info.messageType =
    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  messenger_info.pfnUserCallback = vk::validation::Callback;
  messenger_info.pNext = nullptr;

  //---------------------------
  vk_struct->core.validation.messenger_info = messenger_info;
}
void Messenger::setup_messenger_function(){
  if(!vk_struct->core.validation.enable) return;
  //---------------------------

  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vk_struct->core.instance.handle, "vkCreateDebugUtilsMessengerEXT");
  if(func == nullptr) return;

  VkResult result = func(vk_struct->core.instance.handle, &vk_struct->core.validation.messenger_info, nullptr, &vk_struct->core.validation.messenger);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to set up debug messenger!");
  }

  //---------------------------
}
void Messenger::clean_messenger_function(){
  if(!vk_struct->core.validation.enable) return;
  //---------------------------

  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vk_struct->core.instance.handle, "vkDestroyDebugUtilsMessengerEXT");
  if(func == nullptr) return;

  func(vk_struct->core.instance.handle, vk_struct->core.validation.messenger, nullptr);

  //---------------------------
}

}
