#include "Format.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

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
  else if(format == "BGRA8"){
    vk_format = VK_FORMAT_B8G8R8A8_SRGB;
  }
  else if(format == "R16_UNORM"){
    vk_format = VK_FORMAT_R16_UNORM;
  }
  else if(format == "R16_UINT"){
    vk_format = VK_FORMAT_R16_UINT;
  }
  else if(format == "R32_UINT"){
    vk_format = VK_FORMAT_R32_UINT;
  }
  else if(format == "R16UI"){
    vk_format = VK_FORMAT_R16_UINT;
  }
  else{
    std::cout<<"[error] texture format not recognized [-> "<<format<<"]"<<std::endl;
  }

  //---------------------------
  return vk_format;
}

}
