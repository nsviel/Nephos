#include "Surface.h"

#include <Vulkan/Namespace.h>


namespace vk::presentation{

//Constructor / Destructor
Surface::Surface(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_window = new vk::window::Window(vk_struct);

  //---------------------------
}
Surface::~Surface(){}

//Main function
void Surface::init(){
  //---------------------------

  vk_window->create_surface();

  //---------------------------
}
void Surface::clean(){
  //---------------------------

  vkDestroySurfaceKHR(vk_struct->core.instance.handle, vk_struct->window.surface, nullptr);

  //---------------------------
}

//Subfunction
VkSurfaceFormatKHR Surface::retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& surface_format){
  //---------------------------

  VkFormat required_format = vk_struct->core.swapchain.required_image_format;
  VkColorSpaceKHR required_color_sapce = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

  //Check if standar RGB is available
  for(const auto& format : surface_format){
    if(format.format == required_format && format.colorSpace == required_color_sapce){
      return format;
    }
  }

  std::cout<<"[error] format or standard RGB not available"<<std::endl;

  //---------------------------
  return surface_format[0];
}

}
