#ifndef VK_TEXTURE_H
#define VK_TEXTURE_H

#include "../VK_struct/struct_image.h"
#include "../VK_struct/struct_data.h"
#include "../VK_struct/typedef.h"
#include <ELE_specific/common.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class VK_engine;
class Struct_vulkan;
class VK_buffer;
class VK_image;
class VK_command;


class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(VK_engine* vk_engine);
  ~VK_texture();

public:
  //Main functions
  Struct_image* load_texture_from_file(string path);
  Struct_image* load_texture_from_frame(AVFrame* frame);

  //Texture creation
  void create_texture_from_file(Struct_image* texture, string path);
  void create_texture_from_frame(Struct_image* image, AVFrame* frame);

  //Texture cleaning
  void clean_texture(Struct_data* object);
  void clean_textures();

  //Subfunction
  void create_vulkan_texture(Struct_image* image);
  void copy_buffer_to_image(Struct_image* image, VkBuffer buffer);
  void check_frame_format(AVFrame* frame);
  void convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B);
  void convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* output_data, int output_stride);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_image* vk_image;
  VK_command* vk_command;

  vector<Struct_image*> vec_texture;
};

#endif
