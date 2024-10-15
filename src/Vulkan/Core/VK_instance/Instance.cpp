#include "Instance.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
Instance::Instance(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_layer = new vk::validation::Layer(vk_struct);
  this->vk_messenger = new vk::validation::Messenger(vk_struct);

  //---------------------------
}
Instance::~Instance(){}

//Main function
void Instance::init(){
  //---------------------------

  vk_layer->init_validation_layer();
  this->create_instance();
  vk_messenger->setup_messenger_function();

  //---------------------------
}
void Instance::clean(){
  //---------------------------

  vk_messenger->clean_messenger_function();
  vkDestroyInstance(vk_struct->core.instance.handle, nullptr);

  //---------------------------
}

//Subfunction
void Instance::create_instance(){
  //---------------------------

  //Application info
  VkApplicationInfo app_info{};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "Nephos";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "NoEngine";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_3;

  //Instance info
  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  create_info.enabledExtensionCount = static_cast<uint32_t>(vk_struct->core.instance.extension_instance.size());
  create_info.ppEnabledExtensionNames = vk_struct->core.instance.extension_instance.data();
  create_info.enabledLayerCount = static_cast<uint32_t>(vk_struct->core.validation.vec_layer.size());
  create_info.ppEnabledLayerNames = vk_struct->core.validation.vec_layer.data();
  create_info.pNext = &vk_struct->core.validation.feature_info;

  //Create instance
  VkResult result = vkCreateInstance(&create_info, nullptr, &vk_struct->core.instance.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create vulkan instance");
  }

  //---------------------------
}

}
