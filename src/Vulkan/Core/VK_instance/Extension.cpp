#include "Extension.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
Extension::Extension(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Extension::~Extension(){}

//Main function
void Extension::init(){
  //---------------------------

  this->extension_instance();
  this->extension_window();
  this->extension_device();

  //---------------------------
}

//Subfunction
void Extension::extension_instance(){
  //---------------------------

  vk_struct->core.instance.extension_instance.clear();
  vk_struct->core.instance.extension_instance.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  vk_struct->core.instance.extension_instance.push_back(VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME);
  vk_struct->core.instance.extension_instance.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

  //---------------------------
}
void Extension::extension_device(){
  //---------------------------

  vk_struct->core.instance.extension_device.clear();
  if(!vk_struct->render.param.headless) vk_struct->core.instance.extension_device.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  vk_struct->core.instance.extension_device.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);

  //---------------------------
}
void Extension::extension_window(){
  //---------------------------

  uint32_t glfw_extension_nb = 0;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_nb);
  std::vector<const char*> vec_extension(glfw_extensions, glfw_extensions + glfw_extension_nb);

  for(auto& extension : vec_extension){
    vk_struct->core.instance.extension_instance.push_back(extension);
  }

  //---------------------------
}

}
