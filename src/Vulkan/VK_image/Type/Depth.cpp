#include "Depth.h"

#include <Vulkan/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Depth::Depth(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::create_depth_image(vk::structure::Image* depth){
  //---------------------------

  //Create frame depth image
  depth->name = "tex_depth";
  depth->format = find_depth_format();
  depth->width = vk_struct->window.extent.width;
  depth->height = vk_struct->window.extent.height;
  depth->aspect = VK_IMAGE_ASPECT_DEPTH_BIT;

  vk_image->create_image(depth);

  //---------------------------
}

//Subfunctions
VkFormat Depth::find_depth_format(){
  //---------------------------

  std::vector<VkFormat> format_candidates;
  format_candidates.push_back(VK_FORMAT_D32_SFLOAT);
  format_candidates.push_back(VK_FORMAT_D32_SFLOAT_S8_UINT);
  format_candidates.push_back(VK_FORMAT_D24_UNORM_S8_UINT);

  VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
  VkFormatFeatureFlags features = VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;

  VkFormat format = find_supported_format(format_candidates, tiling, features);

  //---------------------------
  return format;
}
VkFormat Depth::find_supported_format(const std::vector<VkFormat>& format_candidates, VkImageTiling tiling, VkFormatFeatureFlags features){
  //---------------------------

  for(VkFormat format : format_candidates){
    VkFormatProperties property;
    vkGetPhysicalDeviceFormatProperties(vk_struct->device.physical_device.handle, format, &property);

    //tiling
    bool tiling_ok;
    if(tiling == VK_IMAGE_TILING_LINEAR  && (property.linearTilingFeatures & features) == features){
      tiling_ok = true;
    }
    else if(tiling == VK_IMAGE_TILING_OPTIMAL && (property.optimalTilingFeatures & features)){
      tiling_ok = true;
    }
    else{
      tiling_ok = false;
      std::cout<<"[error] Depth format -> tiling not correct"<<endl;
    }

    if(tiling_ok){
      return format;
    }
  }

  throw std::runtime_error("[error] failed to find supported format!");

  //---------------------------
}
bool Depth::find_stencil_component(VkFormat format){
  //For depth image transition
  //---------------------------

  return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;

  //---------------------------
}

}
