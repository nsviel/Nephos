#include "VK_texture.h"
#include "VK_image.h"

#include "../VK_engine.h"
#include "../VK_struct.h"
#include "../Data/VK_buffer.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Command/VK_command.h"

#define STB_IMAGE_IMPLEMENTATION
#include <image/stb_image.h>


//Constructor / Destructor
VK_texture::VK_texture(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_buffer = vk_engine->get_vk_buffer();
  this->vk_image = vk_engine->get_vk_image();

  //---------------------------
}
VK_texture::~VK_texture(){}

//Main function
Struct_image*  VK_texture::load_texture(string path){
  //---------------------------

  Struct_image* texture = new Struct_image();
  texture->path = path;
  texture->format = VK_FORMAT_R8G8B8A8_SRGB;
  texture->aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  this->create_texture(texture);
  this->vec_texture.push_back(texture);

  //---------------------------
  return texture;
}
void VK_texture::clean_texture(Struct_data* data){
  //---------------------------

  for(int i=0; i<data->list_texture.size(); i++){
    Struct_image* texture = *next(data->list_texture.begin(), i);
    vk_image->clean_image(texture);
  }

  //---------------------------
}
void VK_texture::clean_textures(){
  //---------------------------

  for(int i=0; i<vec_texture.size(); i++){
    vk_image->clean_image(vec_texture[i]);
  }

  //---------------------------
}

//Texture creation
void VK_texture::create_texture(Struct_image* image){
  //---------------------------

  this->create_texture_from_file(image);
  vk_image->create_image_view(image);
  vk_image->create_image_sampler(image);

  //---------------------------
}
void VK_texture::create_texture_from_file(Struct_image* image){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  //Load image
  int tex_width, tex_height, tex_channel;
  image->data = stbi_load(image->path.c_str(), &tex_width, &tex_height, &tex_channel, STBI_rgb_alpha);
  image->width = tex_width;
  image->height = tex_height;
  image->size_bytes = tex_width * tex_height * 4;
  if(!image->data){
    throw std::runtime_error("failed to load texture image!");
  }

  //Create vulkan texture
  this->create_vulkan_texture(image);

  //Clean data
  stbi_image_free(image->data);

  //---------------------------
}

//Video creation
void VK_texture::create_texture_from_frame(AVFrame* frame){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  //Create image structure
  Struct_image* image = new Struct_image();
  image->size_bytes = frame->linesize[0] * frame->height;
  image->data = frame->data[0];

  //Create vulkan texture
  this->create_vulkan_texture(image);

  //---------------------------
}

//Subfunction
void VK_texture::create_vulkan_texture(Struct_image* image){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->size_bytes;
  vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_buffer->bind_buffer_memory(MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

  //Copy data to stagging buffer
  void* data;
  vkMapMemory(vk_struct->device.device, staging_mem, 0, tex_size, 0, &data);
  memcpy(data, image->data, static_cast<size_t>(tex_size));
  vkUnmapMemory(vk_struct->device.device, staging_mem);

  //Create image
  image->format = VK_FORMAT_R8G8B8A8_SRGB;
  image->tiling = VK_IMAGE_TILING_OPTIMAL;
  image->image_usage = IMAGE_USAGE_TRANSFERT | IMAGE_USAGE_SAMPLER;
  image->properties = MEMORY_GPU;
  vk_image->create_image(image);

  //Image transition from undefined layout to read only layout
  vk_command->image_layout_transition_single(image, IMAGE_LAYOUT_EMPTY, IMAGE_LAYOUT_TRANSFER_DST);
  this->copy_buffer_to_image(image, staging_buffer);
  vk_command->image_layout_transition_single(image, IMAGE_LAYOUT_TRANSFER_DST, IMAGE_LAYOUT_SHADER_READONLY);

  //Free memory
  vkDestroyBuffer(vk_struct->device.device, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->device.device, staging_mem, nullptr);

  //---------------------------
}
void VK_texture::copy_buffer_to_image(Struct_image* image, VkBuffer buffer){
  VK_command* vk_command = vk_engine->get_vk_command();
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
