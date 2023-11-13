#include "VK_texture.h"

#include <VK_image/VK_image.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_data/VK_buffer.h>
#include <VK_command/VK_command.h>

#define STB_IMAGE_IMPLEMENTATION
#include <image/stb_image.h>


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
Struct_image* VK_texture::load_texture_from_file(string path){
  //---------------------------

  Struct_image* image = new Struct_image();

  this->create_texture_from_file(image, path);
  vk_image->create_image_view(image);
  vk_image->create_image_sampler(image);

  struct_vulkan->data.vec_texture.push_back(image);

  //---------------------------
  return image;
}
Struct_image* VK_texture::load_texture_from_frame(AVFrame* frame){
  //---------------------------

  Struct_image* image = new Struct_image();
  this->create_texture_from_frame(image, frame);
  vk_image->create_image_view(image);
  vk_image->create_image_sampler(image);

  struct_vulkan->data.vec_texture.push_back(image);

  //---------------------------
  return image;
}

//Texture creation
void VK_texture::create_texture_from_file(Struct_image* image, string path){
  //---------------------------

  //File data
  int tex_width, tex_height, tex_channel;
  image->data = stbi_load(path.c_str(), &tex_width, &tex_height, &tex_channel, STBI_rgb_alpha);
  if(!image->data){
    throw std::runtime_error("failed to load texture image!");
  }

  //Image parameters
  image->width = tex_width;
  image->height = tex_height;
  image->format = VK_FORMAT_R8G8B8A8_SRGB;

  //Create vulkan texture
  this->create_vulkan_texture(image);

  //Clean data
  stbi_image_free(image->data);

  //---------------------------
}
void VK_texture::create_texture_from_frame(Struct_image* image, AVFrame* frame){
  //---------------------------

  //Frame data
  int output_stride = frame->width * 4;
  image->data = new uint8_t[output_stride * frame->height];
  convert_YUV420P_to_RGB(frame, image->data, output_stride);

  //Image parameters
  image->width = frame->width;
  image->height = frame->height;
  image->format = VK_FORMAT_R8G8B8A8_SRGB;

  //Create vulkan texture
  this->create_vulkan_texture(image);

  //---------------------------
}

//Texture cleaning
void VK_texture::clean_texture(Struct_entity* data){
  //---------------------------

  for(int i=0; i<data->list_texture.size(); i++){
    Struct_image* image = *next(data->list_texture.begin(), i);
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
void VK_texture::create_vulkan_texture(Struct_image* image){
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
  image->tiling = VK_IMAGE_TILING_OPTIMAL;
  image->aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  image->usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  image->properties = TYP_MEMORY_GPU;
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
void VK_texture::copy_buffer_to_image(Struct_image* image, VkBuffer buffer){
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
void VK_texture::copy_image_to_buffer(Struct_image* image, VkBuffer buffer){
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
void VK_texture::check_frame_format(AVFrame* frame){
  //---------------------------

  switch(frame->format){
    case AV_PIX_FMT_YUV420P:
      say("AV_PIX_FMT_YUV420P");
      break;
    case AV_PIX_FMT_YUV422P:
      say("AV_PIX_FMT_YUV422P");
      break;
    case AV_PIX_FMT_YUV444P:
      say("AV_PIX_FMT_YUV444P");
      break;
    case AV_PIX_FMT_YUYV422:
      say("AV_PIX_FMT_YUYV422");
      break;
    case AV_PIX_FMT_RGB24:
      say("AV_PIX_FMT_RGB24");
      break;
    case AV_PIX_FMT_RGBA:
      say("AV_PIX_FMT_RGBA");
      break;
    default:
      say("format not found");
      break;
  }

  //---------------------------
}
void VK_texture::convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B){
  //---------------------------

  R = Y + 1.13983 * (V - 128);
  G = Y - 0.39465 * (U - 128) - 0.58060 * (V - 128);
  B = Y + 2.03211 * (U - 128);

  // Clamp RGB values to [0, 255]
  R = std::min(255, std::max(0, R));
  G = std::min(255, std::max(0, G));
  B = std::min(255, std::max(0, B));

  //---------------------------
}
void VK_texture::convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* output_data, int output_stride){
  //---------------------------

  int width = frame->width;
  int height = frame->height;
  int Y_stride = frame->linesize[0];
  int U_stride = frame->linesize[1];
  int V_stride = frame->linesize[2];

  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++) {
      int Y = frame->data[0][y * Y_stride + x];
      int U = frame->data[1][y / 2 * U_stride + x / 2];
      int V = frame->data[2][y / 2 * V_stride + x / 2];

      int R, G, B;
      convert_YUV_to_RGB(Y, U, V, R, G, B);

      // Merge channels into VK_FORMAT_R8G8B8A8_UNORM
      uint8_t* pixel = &output_data[y * output_stride + x * 4];
      pixel[0] = static_cast<uint8_t>(R);
      pixel[1] = static_cast<uint8_t>(G);
      pixel[2] = static_cast<uint8_t>(B);
      pixel[3] = 255; // Fully opaque
    }
  }

  //---------------------------
}
