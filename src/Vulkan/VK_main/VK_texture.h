#pragma once

#include <Utility/Specific/common.h>

namespace vk::image{class Image;}
namespace vk::command{class Memory;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}
namespace vk::structure{class Object;}


namespace vk::main{

class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(vk::structure::Vulkan* struct_vulkan);
  ~VK_texture();

public:
  //Main functions
  vk::structure::Image* load_texture(utl::media::Image* image);
  void update_texture(vk::structure::Image* image);
  VkFormat find_texture_format(utl::media::Image* image);

  //Texture cleaning
  void clean_texture(vk::structure::Object* object);
  void clean();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::image::Image* vk_image;
  vk::command::Memory* vk_memory;
};

}
