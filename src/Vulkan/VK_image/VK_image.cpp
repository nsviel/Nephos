#include "VK_image.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_command/VK_memory.h>


//Constructor / Destructor
VK_image::VK_image(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_memory = new VK_memory(struct_vulkan);

  //---------------------------
}
VK_image::~VK_image(){}

//Main function
void VK_image::create_image(vk::structure::Struct_vk_image* image){
  //---------------------------

  this->create_image_obj(image);
  vk_memory->allocate_image_memory(image);
  this->create_image_view(image);
  this->create_image_sampler(image);

  //---------------------------
}
void VK_image::clean_image(vk::structure::Struct_vk_image* image){
  //---------------------------

  vkDestroySampler(struct_vulkan->device.device, image->sampler, nullptr);

  if(image->view != nullptr)
  vkDestroyImageView(struct_vulkan->device.device, image->view, nullptr);
  vkDestroyImage(struct_vulkan->device.device, image->image, nullptr);
  vkFreeMemory(struct_vulkan->device.device, image->mem, nullptr);

  //---------------------------
}

//Image vulkan creation
void VK_image::create_image_obj(vk::structure::Struct_vk_image* image){
  //---------------------------

  VkImageCreateInfo image_info{};
  image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  image_info.imageType = VK_IMAGE_TYPE_2D;
  image_info.extent.width = image->width;
  image_info.extent.height = image->height;
  image_info.extent.depth = 1;
  image_info.mipLevels = image->mip_level;
  image_info.arrayLayers = 1;
  image_info.format = image->format;
  image_info.tiling = image->tiling;
  image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  image_info.usage = image->usage | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
  image_info.samples = VK_SAMPLE_COUNT_1_BIT;
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateImage(struct_vulkan->device.device, &image_info, nullptr, &image->image);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create image!");
  }

  //---------------------------
}
void VK_image::create_image_view(vk::structure::Struct_vk_image* image){
  //---------------------------

  VkImageViewCreateInfo view_info{};
  view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  view_info.subresourceRange = {};
  view_info.subresourceRange.aspectMask = image->aspect;
  view_info.subresourceRange.baseMipLevel = 0;
  view_info.subresourceRange.layerCount = 1;
  view_info.subresourceRange.baseArrayLayer = 0;
  view_info.subresourceRange.levelCount = image->mip_level;
  view_info.format = image->format;
  view_info.image = image->image;
  view_info.flags = 0;

  VkResult result = vkCreateImageView(struct_vulkan->device.device, &view_info, nullptr, &image->view);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create texture image view!");
  }

  //---------------------------
}
void VK_image::create_image_sampler(vk::structure::Struct_vk_image* texture){
  //---------------------------

  VkSamplerCreateInfo sampler_info{};
  sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  sampler_info.magFilter = VK_FILTER_LINEAR;
  sampler_info.minFilter = VK_FILTER_LINEAR;
  sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.anisotropyEnable = VK_TRUE;
  sampler_info.maxAnisotropy = struct_vulkan->device.struct_device.properties.limits.maxSamplerAnisotropy;
  sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  sampler_info.unnormalizedCoordinates = VK_FALSE;
  sampler_info.compareEnable = VK_FALSE;
  sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
  sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  VkResult result = vkCreateSampler(struct_vulkan->device.device, &sampler_info, nullptr, &texture->sampler);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create texture sampler!");
  }

  //---------------------------
}

//subfunction
void VK_image::compute_mipmap(vk::structure::Struct_vk_image* image){
  //---------------------------

  uint32_t max_level = static_cast<uint32_t>(std::floor(std::log2(std::max(image->width, image->height)))) + 1;

  image->mip_level_max = max_level;
  image->mip_level = max_level;

  //Check for mipmap level consistency
  if(image->mip_level > image->mip_level_max){
    image->mip_level = image->mip_level_max;
  }

  //---------------------------
}
void VK_image::generate_mipmap(vk::structure::Struct_vk_image* image){
  //---------------------------


  //---------------------------
}
