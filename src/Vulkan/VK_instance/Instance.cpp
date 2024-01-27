#include "Instance.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
Instance::Instance(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_validation = new vk::validation::Layer(struct_vulkan);

  //---------------------------
}
Instance::~Instance(){}

//Main function
void Instance::init(){
  //---------------------------

  this->create_instance();
  vk_validation->create_validation_layer();

  //---------------------------
}
void Instance::clean(){
  //---------------------------

  vk_validation->clean_layer();
  vkDestroyInstance(struct_vulkan->instance.instance, nullptr);

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
  vector<const char*> validation_layers = vk_validation->get_validation_layers();
  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &appInfo;
  create_info.enabledExtensionCount = static_cast<uint32_t>(struct_vulkan->instance.extension_instance.size());
  create_info.ppEnabledExtensionNames = struct_vulkan->instance.extension_instance.data();
  create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
  create_info.ppEnabledLayerNames = validation_layers.data();
  create_info.pNext = vk_validation->find_validation_extension();

  //Create instance
  VkResult result = vkCreateInstance(&create_info, nullptr, &struct_vulkan->instance.instance);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create instance!");
  }

  //---------------------------
}

}
