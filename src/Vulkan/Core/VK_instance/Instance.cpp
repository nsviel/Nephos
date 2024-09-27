#include "Instance.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
Instance::Instance(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_validation = new vk::validation::Layer(vk_struct);

  //---------------------------
}
Instance::~Instance(){}

//Main function
void Instance::init(){
  //---------------------------

  vk_validation->init_validation_info();
  this->create_instance();
  vk_validation->create_validation_messenger();

  //---------------------------
}
void Instance::clean(){
  //---------------------------

  vk_validation->clean_validation_messenger();
  vkDestroyInstance(vk_struct->core.instance.handle, nullptr);

  //---------------------------
}

//Subfunction
void Instance::create_instance(){
  //---------------------------

  //Application info
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Nephos";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "NoEngine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  //Instance info
  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &appInfo;
  create_info.enabledExtensionCount = static_cast<uint32_t>(vk_struct->core.instance.extension_instance.size());
  create_info.ppEnabledExtensionNames = vk_struct->core.instance.extension_instance.data();
  create_info.enabledLayerCount = static_cast<uint32_t>(vk_struct->core.validation.vec_layer.size());
  create_info.ppEnabledLayerNames = vk_struct->core.validation.vec_layer.data();
  create_info.pNext = &vk_struct->core.validation.feature_info;

  //Create instance
  VkResult result = vkCreateInstance(&create_info, nullptr, &vk_struct->core.instance.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create instance!");
  }

  //---------------------------
}

}
