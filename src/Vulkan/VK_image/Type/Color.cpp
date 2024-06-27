#include "Color.h"

#include <Vulkan/Namespace.h>


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

  vk_image->create_image(color);

  //---------------------------
}

//Subfunction
VkSurfaceFormatKHR Color::retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format){
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : dev_format){
    if(format.format == vk_struct->render.required_image_format && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      return format;
    }
  }

  cout<<"[error] Standard RGB is no available"<<endl;

  //---------------------------
  return dev_format[0];
}
VkFormat Color::find_color_format(){
  VkFormat format;
  //---------------------------

  if(vk_struct->param.headless){
    format = VK_FORMAT_R8G8B8A8_UNORM;
  }else{
    vector<VkSurfaceFormatKHR> surface_format = vk_struct->device.physical_device.formats;
    VkSurfaceFormatKHR surfaceFormat = retrieve_surface_format(surface_format);
    format = surfaceFormat.format;
  }

  //---------------------------
  return format;
}

}
