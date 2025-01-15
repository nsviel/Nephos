#include "Export.h"

#include <Vulkan/Namespace.h>


namespace vk::screenshot{

//Constructor / Destructor
Export::Export(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_format = new vk::screenshot::Format(vk_struct);
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_command_buffer = new vk::commandbuffer::Pool(vk_struct);
  this->vk_allocator = new vk::commandbuffer::Allocator(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Export::~Export(){}

//Main function
void Export::make_screenshot_color(){
  //---------------------------

  vk::structure::Renderpass& renderpass = *vk_struct->graphics.render.renderpass.geometry;
  this->export_image(renderpass.framebuffer.screenshot.color);

  //---------------------------
}
void Export::make_screenshot_depth(){
  //---------------------------

  vk::structure::Renderpass& renderpass = *vk_struct->graphics.render.renderpass.geometry;
  this->export_depth(renderpass.framebuffer.screenshot.depth);

  //---------------------------
}

//Subfunction
void Export::export_image(vk::structure::Image& image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image.width * image.height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_gpu_image_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image.width, image.height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image.format, imageExtent);
  if(bufferSize == 0) return;

  //Save staging buffer data to file
  void* mappedData;
  vkMapMemory(vk_struct->core.device.handle, staging_mem, 0, bufferSize, 0, &mappedData);

  // Invert red and green channels
  unsigned char* pixelData = static_cast<unsigned char*>(mappedData);
  for(int i = 0; i < image.width * image.height; i++){
    // RGBA format: pixelData[4 * i] = R, pixelData[4 * i + 1] = G, pixelData[4 * i + 2] = B, pixelData[4 * i + 3] = A
    std::swap(pixelData[4 * i], pixelData[4 * i + 2]);  // Swap R (index 0) and G (index 1)
  }

  vk_format->export_to_format(image, pixelData);

  vkUnmapMemory(vk_struct->core.device.handle, staging_mem);

  //Free memory
  vkDestroyBuffer(vk_struct->core.device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->core.device.handle, staging_mem, nullptr);

  //---------------------------
}
void Export::export_depth(vk::structure::Image& image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image.width * image.height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_gpu_depth_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image.width, image.height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image.format, imageExtent);
  if(bufferSize == 0) return;

  //Save staging buffer data to file
  void* mappedData;
  vkMapMemory(vk_struct->core.device.handle, staging_mem, 0, bufferSize, 0, &mappedData);

  // Normalize depth data to 8-bit grayscale
  float* depthData = static_cast<float*>(mappedData);
  std::vector<uint8_t> grayscaleData(image.width * image.height);
  for (uint32_t i = 0; i < image.width * image.height; ++i) {
      float depth = depthData[i];
      grayscaleData[i] = static_cast<uint8_t>(std::clamp(depth * 255.0f, 0.0f, 255.0f)); // Normalize depth to 0-255
  }
  image.channel_nb = 1;

  vk_format->export_to_format(image, grayscaleData.data());

  vkUnmapMemory(vk_struct->core.device.handle, staging_mem);

  //Free memory
  vkDestroyBuffer(vk_struct->core.device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->core.device.handle, staging_mem, nullptr);

  //---------------------------
}
VkDeviceSize Export::calculate_image_size(VkFormat format, VkExtent3D extent){
  //---------------------------

  // Get the number of bytes per pixel for the specified format
  VkFormatProperties formatProperties;
  vkGetPhysicalDeviceFormatProperties(vk_struct->core.device.physical_device.handle, format, &formatProperties);

  if((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == 0){
    // Format does not support linear tiling, use optimal tiling instead
    // You may need to handle this differently based on your specific requirements
    // In this example, we'll assume optimal tiling support
    vkGetPhysicalDeviceFormatProperties(vk_struct->core.device.physical_device.handle, format, &formatProperties);
  }

  VkDeviceSize bytesPerPixel = 0;

  switch (format){
    case VK_FORMAT_R8_UNORM:
      bytesPerPixel = 1;
      break;
    case VK_FORMAT_R8G8_UNORM:
      bytesPerPixel = 2;
      break;
    case VK_FORMAT_R8G8B8A8_UNORM:
      bytesPerPixel = 4;
      break;
    case VK_FORMAT_B8G8R8A8_UNORM:
      bytesPerPixel = 4;
      break;
    case VK_FORMAT_R8G8B8A8_SRGB:
      bytesPerPixel = 4;
      break;

    // Add case for depth formats
    case VK_FORMAT_D32_SFLOAT:
    case VK_FORMAT_D32_SFLOAT_S8_UINT:
    case VK_FORMAT_D24_UNORM_S8_UINT:
    case VK_FORMAT_S8_UINT:
      bytesPerPixel = 4; // Typically, depth formats are 4 bytes (float or int)
      break;

    default:
      throw std::runtime_error("Unsupported image format");
      return 0;
  }

  // Calculate the size of the image buffer
  VkDeviceSize imageSize = bytesPerPixel * extent.width * extent.height * extent.depth;

  //---------------------------
  return imageSize;
}

}
