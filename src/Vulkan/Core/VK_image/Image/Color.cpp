#include "Color.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Color::Color(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::create_color_image(vk::structure::Image* color){
  //---------------------------

  //Create frame color image
  color->name = "tex_color";
  color->format = find_color_format();
  color->width = vk_struct->window.extent.width;
  color->height = vk_struct->window.extent.height;
  color->aspect = VK_IMAGE_ASPECT_COLOR_BIT;

  vk_image->create_image(*color);

  //---------------------------
}

//Subfunction
VkSurfaceFormatKHR Color::retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& surface_format){
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
VkFormat Color::find_color_format(){
  VkFormat format;
  //---------------------------

  if(vk_struct->interface.param.headless){
    format = VK_FORMAT_R8G8B8A8_UNORM;
  }else{
    std::vector<VkSurfaceFormatKHR> vec_surface_format = vk_struct->core.device.physical_device.vec_surface_format;
    VkSurfaceFormatKHR surface_format = retrieve_surface_format(vec_surface_format);
    format = surface_format.format;
  }

  //---------------------------
  return format;
}

}
