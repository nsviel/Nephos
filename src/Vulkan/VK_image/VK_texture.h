#ifndef VK_TEXTURE_H
#define VK_TEXTURE_H

#include <VK_struct/Struct_image.h>
#include <VK_struct/Struct_entity.h>
#include <VK_struct/typedef.h>
#include <ELE_specific/common.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class Struct_vulkan;
class VK_buffer;
class VK_image;
class VK_command;


class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(Struct_vulkan* struct_vulkan);
  ~VK_texture();

public:
  //Main functions
  Struct_image* load_texture_from_file(string path);
  Struct_image* load_texture_from_frame(AVFrame* frame);
  Struct_image* load_texture_from_bin(string path);

  void update_texture_from_frame(Struct_image* image, AVFrame* frame);

  //Texture creation
  void create_texture_from_file(Struct_image* texture, string path);
  void create_texture_from_frame(Struct_image* image, AVFrame* frame);
  void create_texture_from_bin(Struct_image* image, string path);

  //Texture cleaning
  void clean_texture(Struct_entity* object);
  void clean_textures();

  //Subfunction
  void create_vulkan_texture(Struct_image* image);
  void update_vulkan_texture(Struct_image* image);
  void copy_buffer_to_image(Struct_image* image, VkBuffer buffer);
  void copy_image_to_buffer(Struct_image* image, VkBuffer buffer);
  void check_frame_format(AVFrame* frame);
  void convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B);
  void convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* output_data, int output_stride);
  VkDeviceSize calculateImageSize(VkFormat format, VkExtent3D extent);

  void make_screenshot(Struct_image* image);
  void save_to_bin(Struct_image* image);

private:
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_image* vk_image;
  VK_command* vk_command;
};

#endif
