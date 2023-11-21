#include "VK_depth.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_image/VK_image.h>


//Constructor / Destructor
VK_depth::VK_depth(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_image = new VK_image(struct_vulkan);

  //---------------------------
}
VK_depth::~VK_depth(){}

//Main function
void VK_depth::create_depth_attachment(Struct_vk_image* depth){
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
void VK_depth::clean_depth_attachment(Struct_vk_image* depth){
  //---------------------------

  vkDestroyImageView(struct_vulkan->device.device, depth->view, nullptr);
  vkDestroyImage(struct_vulkan->device.device, depth->image, nullptr);
  vkFreeMemory(struct_vulkan->device.device, depth->mem, nullptr);

  //---------------------------
}

//Subfunctions
VkFormat VK_depth::find_depth_format(){
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
VkFormat VK_depth::find_supported_format(const std::vector<VkFormat>& format_candidates, VkImageTiling tiling, VkFormatFeatureFlags features){
  //---------------------------

  for(VkFormat format : format_candidates){
    VkFormatProperties property;
    vkGetPhysicalDeviceFormatProperties(struct_vulkan->device.struct_device.physical_device, format, &property);

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
bool VK_depth::find_stencil_component(VkFormat format){
  //For depth image transition
  //---------------------------

  return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;

  //---------------------------
}
