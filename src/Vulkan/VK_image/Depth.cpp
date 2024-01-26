#include "Depth.h"

#include <Vulkan/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Depth::Depth(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_image = new vk::image::VK_image(struct_vulkan);

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::create_depth_image(vk::structure::Image* depth){
  //---------------------------

  //Create frame depth image
  depth->name = "tex_depth";
  depth->format = find_depth_format();
  depth->width = struct_vulkan->window.extent.width;
  depth->height = struct_vulkan->window.extent.height;
  depth->aspect = VK_IMAGE_ASPECT_DEPTH_BIT;

  vk_image->create_image(depth);

  //---------------------------
}

//Subfunctions
VkFormat Depth::find_depth_format(){
  //---------------------------

  vector<VkFormat> format_candidates;
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
    vkGetPhysicalDeviceFormatProperties(struct_vulkan->device.physical_device.physical_device, format, &property);

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
      cout<<"[error] Depth format -> tiling not correct"<<endl;
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
