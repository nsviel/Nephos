#pragma once

#include <VK_struct/Struct_vk_image.h>
#include <VK_struct/Struct_vk_entity.h>
#include <VK_struct/VK_typedef.h>
#include <UTL_specific/common.h>
#include <UTL_base/Struct_image.h>

class Struct_vulkan;
class VK_image;
class VK_memory;

class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(Struct_vulkan* struct_vulkan);
  ~VK_texture();

public:
  //Main functions
  Struct_vk_image* load_texture(data::Image* image);
  void update_texture(Struct_vk_image* image);
  VkFormat find_texture_format(data::Image* image);

  //Texture cleaning
  void clean_texture(Struct_vk_entity* object);
  void clean_textures();

private:
  Struct_vulkan* struct_vulkan;
  VK_image* vk_image;
  VK_memory* vk_memory;
};
