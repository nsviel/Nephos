#include "Format.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>

/*
VK_FORMAT_R8G8B8A8_SRGB : for color image
VK_FORMAT_D32_SFLOAT : for depth image
VK_FORMAT_R32G32_SFLOAT : for high precision texture
*/


namespace vk::image{

//Constructor / Destructor
Format::Format(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Format::~Format(){}

//Main function
VkFormat Format::find_vk_format(std::string format){
  VkFormat vk_format = VK_FORMAT_UNDEFINED;
  //---------------------------

  if(format == "RGBA8"){
    vk_format = VK_FORMAT_R8G8B8A8_SRGB;
  }
  else if(format == "RG32"){
    vk_format = VK_FORMAT_R32G32_SFLOAT;
  }
  else if(format == "R16_UINT"){
    vk_format = VK_FORMAT_R16_UINT;
  }
  else{
    std::cout<<"[error] texture format not recognized [-> "<<format<<"]"<<std::endl;
  }

  //---------------------------
  return vk_format;
}
VkImageUsageFlags Format::find_usage_from_format(vk::structure::Image& image){
  VkImageUsageFlags usage = image.usage;
  //---------------------------

  if(image.format == VK_FORMAT_B8G8R8A8_SRGB) sayHello();

  switch(image.format){
    case VK_FORMAT_D32_SFLOAT:
    case VK_FORMAT_R16_UINT:
    case VK_FORMAT_B8G8R8A8_UNORM:
    case VK_FORMAT_R32G32_SFLOAT:
    case VK_FORMAT_R8G8B8A8_SRGB:
    case VK_FORMAT_B8G8R8A8_SRGB:{
      usage |= VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
      break;
    }
    /*case VK_FORMAT_R32G32_SFLOAT:
    case VK_FORMAT_R16_UINT:{
      usage |= VK_IMAGE_USAGE_STORAGE_BIT;
      break;
    }*/
  }

  //---------------------------
  return usage;
}
bool Format::check_image_format(vk::structure::Image& image){
  //---------------------------

  VkImageFormatProperties format_property;
  VkResult result = vkGetPhysicalDeviceImageFormatProperties(
    vk_struct->core.device.physical_device.handle,
    image.format,
    VK_IMAGE_TYPE_2D,
    VK_IMAGE_TILING_OPTIMAL,
    VK_IMAGE_USAGE_STORAGE_BIT,
    0,
    &format_property
  );

  if(result == VK_SUCCESS){
    return true;
  }else{
    std::cout<<"[error] image format not supported by device"<<std::endl;
    return false;
  }

  //---------------------------
}


}
