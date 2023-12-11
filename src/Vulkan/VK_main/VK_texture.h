#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/VK_typedef.h>
#include <Utility/Specific/common.h>
#include <Utility/Base/Struct_image.h>


class VK_image;
class VK_memory;

class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(vk::structure::Vulkan* struct_vulkan);
  ~VK_texture();

public:
  //Main functions
  vk::structure::Image* load_texture(utility::base::Image* image);
  void update_texture(vk::structure::Image* image);
  VkFormat find_texture_format(utility::base::Image* image);

  //Texture cleaning
  void clean_texture(vk::structure::Entity* object);
  void clean_textures();

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_image* vk_image;
  VK_memory* vk_memory;
};
