#include "VK_texture.h"

#include <VK_image/VK_image.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_data/VK_buffer.h>
#include <VK_command/VK_command.h>
#include <UTL_file/File.h>
#include <UTL_file/Image.h>


//Constructor / Destructor
VK_texture::VK_texture(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_buffer = new VK_buffer(struct_vulkan);
  this->vk_image = new VK_image(struct_vulkan);
  this->vk_command = new VK_command(struct_vulkan);

  //---------------------------
}
VK_texture::~VK_texture(){}

//Main function
Struct_vk_image* VK_texture::load_texture(Struct_image* struct_image){
  //---------------------------

  Struct_vk_image* image = new Struct_vk_image();
  image->data = struct_image->buffer;
  image->width = struct_image->width;
  image->height = struct_image->height;
  image->format = find_texture_format(struct_image);
  image->aspect = find_texture_aspect(struct_image);
  this->create_vulkan_texture(image);
  struct_vulkan->data.vec_texture.push_back(image);

  //---------------------------
  return image;
}
void VK_texture::update_texture_from_data(Struct_vk_image* image, uint8_t* data){
  //---------------------------

  //Frame data
  image->data = data;

  //Create vulkan texture
  this->update_vulkan_texture(image);

  //---------------------------
}

//Texture cleaning
void VK_texture::clean_texture(Struct_vk_entity* data){
  //---------------------------

  for(int i=0; i<data->list_texture.size(); i++){
    Struct_vk_image* image = *next(data->list_texture.begin(), i);
    vk_image->clean_image(image);
  }

  //---------------------------
}
void VK_texture::clean_textures(){
  //---------------------------

  for(int i=0; i<struct_vulkan->data.vec_texture.size(); i++){
    vk_image->clean_image(struct_vulkan->data.vec_texture[i]);
  }

  //---------------------------
}

//Subfunction
void VK_texture::create_vulkan_texture(Struct_vk_image* image){
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_buffer->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

  //Copy data to stagging buffer
  void* data;
  vkMapMemory(struct_vulkan->device.device, staging_mem, 0, tex_size, 0, &data);
  memcpy(data, image->data, static_cast<size_t>(tex_size));
  vkUnmapMemory(struct_vulkan->device.device, staging_mem);

  //Create image
  image->aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  image->usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  vk_image->create_image(image);

  //Image transition from undefined layout to read only layout
  vk_command->image_layout_transition_single(image, TYP_IMAGE_LAYOUT_EMPTY, TYP_IMAGE_LAYOUT_TRANSFER_DST);
  this->copy_buffer_to_image(image, staging_buffer);
  vk_command->image_layout_transition_single(image, TYP_IMAGE_LAYOUT_TRANSFER_DST, TYP_IMAGE_LAYOUT_SHADER_READONLY);

  //Free memory
  vkDestroyBuffer(struct_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(struct_vulkan->device.device, staging_mem, nullptr);

  //---------------------------
}
void VK_texture::update_vulkan_texture(Struct_vk_image* image){
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_buffer->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

  //Copy data to stagging buffer
  void* data;
  vkMapMemory(struct_vulkan->device.device, staging_mem, 0, tex_size, 0, &data);
  memcpy(data, image->data, static_cast<size_t>(tex_size));
  vkUnmapMemory(struct_vulkan->device.device, staging_mem);

  //Image transition from undefined layout to read only layout
  vk_command->image_layout_transition_single(image, TYP_IMAGE_LAYOUT_EMPTY, TYP_IMAGE_LAYOUT_TRANSFER_DST);
  this->copy_buffer_to_image(image, staging_buffer);
  vk_command->image_layout_transition_single(image, TYP_IMAGE_LAYOUT_TRANSFER_DST, TYP_IMAGE_LAYOUT_SHADER_READONLY);

  //Free memory
  vkDestroyBuffer(struct_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(struct_vulkan->device.device, staging_mem, nullptr);

  //---------------------------
}
void VK_texture::copy_buffer_to_image(Struct_vk_image* image, VkBuffer buffer){
  //---------------------------

  VkCommandBuffer command_buffer = vk_command->singletime_command_begin();

  VkBufferImageCopy region{};
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;

  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;

  region.imageOffset = {0, 0, 0};
  region.imageExtent = {
    image->width,
    image->height,
    1
  };

  vkCmdCopyBufferToImage(command_buffer, buffer, image->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  vk_command->singletime_command_end(command_buffer);

  //---------------------------
}
void VK_texture::copy_image_to_buffer(Struct_vk_image* image, VkBuffer buffer){
  //---------------------------

  VkCommandBuffer command_buffer = vk_command->singletime_command_begin();

  VkBufferImageCopy copyRegion = {
    .bufferOffset = 0,
    .bufferRowLength = 0,
    .bufferImageHeight = 0,
    .imageSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
    .imageOffset = {0, 0, 0},
    .imageExtent = {image->width, image->height, 1} // Adjust dimensions accordingly
  };

  vkCmdCopyImageToBuffer(command_buffer, image->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &copyRegion);

  vk_command->singletime_command_end(command_buffer);

  //---------------------------
}
VkFormat VK_texture::find_texture_format(Struct_image* image){
  VkFormat format;
  //---------------------------

  if(image->format == "R8G8B8A8_SRGB"){
    format = VK_FORMAT_R8G8B8A8_SRGB;
  }
  else if(image->format == "B8G8R8A8_SRGB"){
    format = VK_FORMAT_B8G8R8A8_SRGB;
  }
  else if(image->format == "R16_UNORM"){
    format = VK_FORMAT_R16_UNORM;
  }
  else if(image->format == "R32_UINT"){
    format = VK_FORMAT_R32_UINT;
  }
  else if(image->format == "R16UI"){
    format = VK_FORMAT_R16_UINT;
  }
  else{
    cout<<"[error] texture format not recognized ["<<image->format<<"]"<<endl;
  }

  //---------------------------
  return format;
}
VkImageAspectFlags VK_texture::find_texture_aspect(Struct_image* image){
  VkImageAspectFlags aspect;
  //---------------------------

  if(image->format == "R8G8B8A8_SRGB"){
    aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  }
  else if(image->format == "B8G8R8A8_SRGB"){
    aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  }
  else if(image->format == "R16_UNORM"){
    aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  }
  else if(image->format == "R32_UINT"){
    aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  }
  else if(image->format == "R16UI"){
    aspect = VK_IMAGE_ASPECT_DEPTH_BIT;
  }
  else{
    cout<<"[error] texture format not recognized ["<<image->format<<"]"<<endl;
  }

  //---------------------------
  return aspect;
}
