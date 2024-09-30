#include "Image.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Image::Image(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::create_image(vk::structure::Image& image){
  if(!check_image_format(image)) return;
  //---------------------------

  this->create_image_handle(image);
  vk_mem_allocator->allocate_image_memory(image);
  this->create_image_view(image);
  this->create_image_sampler(image);

  //---------------------------
}
void Image::clean_image(vk::structure::Image& image){
  //---------------------------

  vkDestroySampler(vk_struct->core.device.handle, image.sampler, nullptr);

  if(image.view != nullptr)
  this->clean_image_view(image);
  vkDestroyImage(vk_struct->core.device.handle, image.handle, nullptr);
  vkFreeMemory(vk_struct->core.device.handle, image.mem, nullptr);

  //---------------------------
}
void Image::clean_image_view(vk::structure::Image& image){
  //---------------------------

  vkDestroyImageView(vk_struct->core.device.handle, image.view, nullptr);

  //---------------------------
}

//Subfunction
void Image::create_image_handle(vk::structure::Image& image){
  //---------------------------

  VkImageCreateInfo image_info{};
  image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  image_info.imageType = VK_IMAGE_TYPE_2D;
  image_info.extent.width = image.width;
  image_info.extent.height = image.height;
  image_info.extent.depth = 1;
  image_info.mipLevels = image.mip_level;
  image_info.arrayLayers = 1;
  image_info.format = image.format;
  image_info.tiling = image.tiling;
  image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  image_info.usage = image.usage | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
  image_info.samples = vk_struct->core.device.physical_device.max_sample_count;
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateImage(vk_struct->core.device.handle, &image_info, nullptr, &image.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create image!");
  }

  //---------------------------
}
void Image::create_image_view(vk::structure::Image& image){
  //---------------------------

  VkImageViewCreateInfo view_info{};
  view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  view_info.subresourceRange = {};
  view_info.subresourceRange.aspectMask = image.aspect;
  view_info.subresourceRange.baseMipLevel = 0;
  view_info.subresourceRange.layerCount = 1;
  view_info.subresourceRange.baseArrayLayer = 0;
  view_info.subresourceRange.levelCount = image.mip_level;
  view_info.format = image.format;
  view_info.image = image.handle;
  view_info.flags = 0;

  VkResult result = vkCreateImageView(vk_struct->core.device.handle, &view_info, nullptr, &image.view);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create image view!");
  }

  //---------------------------
}
void Image::create_image_sampler(vk::structure::Image& image){
  //---------------------------

  VkSamplerCreateInfo sampler_info{};
  sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  sampler_info.magFilter = VK_FILTER_LINEAR;
  sampler_info.minFilter = VK_FILTER_LINEAR;
  sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.anisotropyEnable = VK_TRUE;
  sampler_info.maxAnisotropy = vk_struct->core.device.physical_device.properties.limits.maxSamplerAnisotropy;
  sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  sampler_info.unnormalizedCoordinates = VK_FALSE;
  sampler_info.compareEnable = VK_FALSE;
  sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
  sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  VkResult result = vkCreateSampler(vk_struct->core.device.handle, &sampler_info, nullptr, &image.sampler);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create image sampler!");
  }

  //---------------------------
}
bool Image::check_image_format(vk::structure::Image& image){
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
