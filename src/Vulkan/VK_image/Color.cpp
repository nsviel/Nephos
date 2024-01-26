#include "Color.h"

#include <Vulkan/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Color::Color(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_image = new VK_image(struct_vulkan);

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::create_color_image(vk::structure::Image* color){
  //---------------------------

  //Create frame color image
  color->name = "tex_color";
  color->format = find_color_format();
  color->width = struct_vulkan->window.extent.width;
  color->height = struct_vulkan->window.extent.height;
  color->aspect = VK_IMAGE_ASPECT_COLOR_BIT;

  vk_image->create_image(color);

  //---------------------------
}

//Subfunction
VkSurfaceFormatKHR Color::retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format){
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : dev_format){
    if(format.format == struct_vulkan->render.required_image_format && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
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

  if(struct_vulkan->param.headless){
    format = VK_FORMAT_R8G8B8A8_UNORM;
  }else{
    vector<VkSurfaceFormatKHR> surface_format = struct_vulkan->device.physical_device.formats;
    VkSurfaceFormatKHR surfaceFormat = retrieve_surface_format(surface_format);
    format = surfaceFormat.format;
  }

  //---------------------------
  return format;
}

}
