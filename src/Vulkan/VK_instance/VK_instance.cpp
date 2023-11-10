#include "VK_instance.h"

#include <VK_instance/VK_validation.h>
#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>


//Constructor / Destructor
VK_instance::VK_instance(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_validation = new VK_validation(struct_vulkan);

  struct_vulkan->instance.extension.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

  //---------------------------
}
VK_instance::~VK_instance(){}

//Main function
void VK_instance::init_instance(){
  //---------------------------

  this->create_instance();
  vk_validation->create_validation_layer();

  //---------------------------
}
void VK_instance::clean_instance(){
  //---------------------------

  vk_validation->clean_layer();
  vkDestroyInstance(struct_vulkan->instance.instance, nullptr);

  //---------------------------
}

//Subfunction
void VK_instance::create_instance(){
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
  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(struct_vulkan->instance.extension.size());
  createInfo.ppEnabledExtensionNames = struct_vulkan->instance.extension.data();
  createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
  createInfo.ppEnabledLayerNames = validation_layers.data();
  createInfo.pNext = vk_validation->find_validation_extension();

  //Create instance
  VkResult result = vkCreateInstance(&createInfo, nullptr, &struct_vulkan->instance.instance);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create instance!");
  }

  //---------------------------
}
