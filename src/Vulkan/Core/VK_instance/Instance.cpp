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
  vk_validation->create_validation_layer();
  this->create_instance();


  //---------------------------
}
void Instance::clean(){
  //---------------------------

  vk_validation->clean_validation_layer();
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
  std::vector<const char*> validation_layers = vk_validation->get_validation_layers();
  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &appInfo;
  create_info.enabledExtensionCount = static_cast<uint32_t>(vk_struct->core.instance.extension_instance.size());
  create_info.ppEnabledExtensionNames = vk_struct->core.instance.extension_instance.data();
  create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
  create_info.ppEnabledLayerNames = validation_layers.data();
  create_info.pNext = vk_validation->find_validation_extension();

  //Create instance
  VkResult result = vkCreateInstance(&create_info, nullptr, &vk_struct->core.instance.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create instance!");
  }

  //---------------------------
}

}
