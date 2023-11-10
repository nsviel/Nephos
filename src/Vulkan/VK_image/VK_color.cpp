#include "VK_color.h"

#include <VK_image/VK_depth.h>
#include <VK_image/VK_image.h>
#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_device/VK_physical_device.h>
#include <VK_presentation/VK_framebuffer.h>


//Constructor / Destructor
VK_color::VK_color(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_physical_device = new VK_physical_device(struct_vulkan);
  this->vk_image = new VK_image(struct_vulkan);

  //---------------------------
}
VK_color::~VK_color(){}

//Main function
void VK_color::create_color_attachment(Struct_image* color){
  //---------------------------

  //Create frame color image
  color->name = "tex_color";
  color->format = find_color_format();
  color->width = struct_vulkan->window.extent.width;
  color->height = struct_vulkan->window.extent.height;
  color->tiling = VK_IMAGE_TILING_OPTIMAL;
  color->properties = MEMORY_GPU;
  color->aspect = VK_IMAGE_ASPECT_COLOR_BIT;

  vk_image->create_image(color);
  vk_image->create_image_view(color);
  vk_image->create_image_sampler(color);

  //---------------------------
}

//Subfunction
VkSurfaceFormatKHR VK_color::retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format){
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : dev_format){
    if(format.format == struct_vulkan->render.required_image_format && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      return format;
    }
  }

  cout<<"[error] Standar RGB is no available"<<endl;

  //---------------------------
  return dev_format[0];
}
VkFormat VK_color::find_color_format(){
  //---------------------------

  vector<VkSurfaceFormatKHR> surface_format = struct_vulkan->device.struct_device.formats;
  VkSurfaceFormatKHR surfaceFormat = retrieve_surface_format(surface_format);
  VkFormat format = surfaceFormat.format;

  //---------------------------
  return format;
}
