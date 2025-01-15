#include "Color.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Color::Color(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::create_window_image(vk::structure::Image* color){
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
void Color::create_screenshot_image(vk::structure::Image* color){
  //---------------------------

  //Create frame color image
  color->name = "tex_color";
  color->format = find_color_format();
  color->width = 3840;
  color->height = 2160;
  color->aspect = VK_IMAGE_ASPECT_COLOR_BIT;

  vk_image->create_image(*color);

  //---------------------------
}

//Subfunction
VkFormat Color::find_color_format(){
  VkFormat format;
  //---------------------------

  if(vk_struct->interface.param.headless){
    format = VK_FORMAT_R8G8B8A8_UNORM;
  }else{
    std::vector<VkSurfaceFormatKHR> vec_surface_format = vk_struct->core.device.physical_device.vec_surface_format;
    VkSurfaceFormatKHR surface_format = vk_surface->retrieve_surface_format(vec_surface_format);
    format = surface_format.format;
  }

  //---------------------------
  return format;
}

}
