#ifndef VK_TEXTURE_H
#define VK_TEXTURE_H

#include <VK_struct/Struct_vk_image.h>
#include <VK_struct/Struct_vk_entity.h>
#include <VK_struct/VK_typedef.h>
#include <UTL_specific/common.h>
#include <UTL_struct/Struct_image.h>

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
  Struct_vk_image* load_texture(Struct_image* struct_image);
  void update_texture_from_data(Struct_vk_image* image, uint8_t* data);

  //Texture cleaning
  void clean_texture(Struct_vk_entity* object);
  void clean_textures();

  //Subfunction
  void create_vulkan_texture(Struct_vk_image* image);
  void update_vulkan_texture(Struct_vk_image* image);
  void copy_buffer_to_image(Struct_vk_image* image, VkBuffer buffer);
  void copy_image_to_buffer(Struct_vk_image* image, VkBuffer buffer);
  VkFormat find_texture_format(Struct_image* image);
  VkImageAspectFlags find_texture_aspect(Struct_image* image);

private:
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_image* vk_image;
  VK_command* vk_command;
};

#endif
