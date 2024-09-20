#include "Format.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Format::Format(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_screenshot = new vk::image::Screenshot(vk_struct);

  //---------------------------
}
Format::~Format(){}

//Main function
VkFormat Format::find_texture_format(std::shared_ptr<utl::media::Image> image){
  VkFormat format = VK_FORMAT_UNDEFINED;
  //---------------------------

  if(image->format == "RGBA8"){
    format = VK_FORMAT_R8G8B8A8_SRGB;
  }
  else if(image->format == "BGRA8"){
    format = VK_FORMAT_B8G8R8A8_SRGB;
  }
  else if(image->format == "R16_UNORM"){
    format = VK_FORMAT_R16_UNORM;
  }
  else if(image->format == "R16_UINT"){
    format = VK_FORMAT_R16_UINT;
  }
  else if(image->format == "R32_UINT"){
    format = VK_FORMAT_R32_UINT;
  }
  else if(image->format == "R16UI"){
    format = VK_FORMAT_R16_UINT;
  }
  else{
    std::cout<<"[error] texture format not recognized [-> "<<image->format<<"]"<<std::endl;
  }

  //---------------------------
  return format;
}

}
