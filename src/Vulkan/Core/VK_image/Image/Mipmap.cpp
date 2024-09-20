#include "Mipmap.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Mipmap::Mipmap(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Mipmap::~Mipmap(){}

//Main function
void Mipmap::compute_mipmap(vk::structure::Image& image){
  //---------------------------

  uint32_t max_level = static_cast<uint32_t>(std::floor(std::log2(std::max(image.width, image.height)))) + 1;

  image.mip_level_max = max_level;
  image.mip_level = max_level;

  //Check for mipmap level consistency
  if(image.mip_level > image.mip_level_max){
    image.mip_level = image.mip_level_max;
  }

  //---------------------------
}
void Mipmap::generate_mipmap(vk::structure::Image& image){
  //---------------------------


  //---------------------------
}

}
