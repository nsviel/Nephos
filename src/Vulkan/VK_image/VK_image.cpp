#include "VK_image.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_data/VK_buffer.h>


//Constructor / Destructor
VK_image::VK_image(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_buffer = new VK_buffer(struct_vulkan);

  //---------------------------
}
VK_image::~VK_image(){}

//Generic image creation
void VK_image::clean_image(Struct_image* image){
  //---------------------------

  vkDestroySampler(struct_vulkan->device.device, image->sampler, nullptr);

  if(image->view != nullptr)
  vkDestroyImageView(struct_vulkan->device.device, image->view, nullptr);
  vkDestroyImage(struct_vulkan->device.device, image->image, nullptr);
  vkFreeMemory(struct_vulkan->device.device, image->mem, nullptr);

  //---------------------------
}
void VK_image::create_image_view(Struct_image* image){
  //---------------------------

  VkImageViewCreateInfo viewInfo{};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = image->format;
  viewInfo.subresourceRange = {};
  viewInfo.subresourceRange.aspectMask = image->aspect;
  viewInfo.subresourceRange.baseMipLevel = 0;
  viewInfo.subresourceRange.levelCount = image->mip_level;
  viewInfo.subresourceRange.baseArrayLayer = 0;
  viewInfo.subresourceRange.layerCount = 1;
  viewInfo.image = image->image;
  viewInfo.flags = 0;

  VkImageView imageView;
  VkResult result = vkCreateImageView(struct_vulkan->device.device, &viewInfo, nullptr, &image->view);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create texture image view!");
  }

  this->compute_mipmap(image);

  //---------------------------
}
VkImageView VK_image::create_image_view(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags){
	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = aspectFlags;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;
	if (vkCreateImageView(struct_vulkan->device.device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create texture image view!");
	}

	return imageView;
}
void VK_image::create_image_sampler(Struct_image* texture){
  //---------------------------

  VkSamplerCreateInfo samplerInfo{};
  samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  samplerInfo.magFilter = VK_FILTER_LINEAR;
  samplerInfo.minFilter = VK_FILTER_LINEAR;
  samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.anisotropyEnable = VK_TRUE;
  samplerInfo.maxAnisotropy = struct_vulkan->device.struct_device.properties.limits.maxSamplerAnisotropy;
  samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  samplerInfo.unnormalizedCoordinates = VK_FALSE;
  samplerInfo.compareEnable = VK_FALSE;
  samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
  samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  VkResult result = vkCreateSampler(struct_vulkan->device.device, &samplerInfo, nullptr, &texture->sampler);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create texture sampler!");
  }

  //---------------------------
}

//Image creation subfunction
void VK_image::create_image(Struct_image* image){
  //---------------------------

  this->create_image_obj(image);
  this->bind_image_to_memory(image);

  //---------------------------
}
void VK_image::create_image_obj(Struct_image* image){
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
  image_info.usage = image->usage | VK_IMAGE_USAGE_SAMPLED_BIT;
  image_info.samples = VK_SAMPLE_COUNT_1_BIT;
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateImage(struct_vulkan->device.device, &image_info, nullptr, &image->image);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create image!");
  }

  //---------------------------
}
void VK_image::bind_image_to_memory(Struct_image* image){
  //---------------------------

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(struct_vulkan->device.device, image->image, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = vk_buffer->findMemoryType(memRequirements.memoryTypeBits, image->properties);

  VkResult result = vkAllocateMemory(struct_vulkan->device.device, &allocInfo, nullptr, &image->mem);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(struct_vulkan->device.device, image->image, image->mem, 0);

  //---------------------------
}

//subfunction
void VK_image::compute_mipmap(Struct_image* image){
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
void VK_image::generate_mipmap(Struct_image* image){
  //---------------------------


  //---------------------------
}
