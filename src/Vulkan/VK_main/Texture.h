#pragma once

#include <Utility/Specific/common.h>

namespace vk::image{class Image;}
namespace vk::command{class Memory;}
namespace vk::command{class Transfert;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Texture;}
namespace vk::structure{class Object;}
namespace vk::data{class Buffer;}


namespace vk::main{

class Texture
{
public:
  //Constructor / Destructor
  Texture(vk::structure::Vulkan* struct_vulkan);
  ~Texture();

public:
  //Main functions
  vk::structure::Texture* load_texture(utl::media::Image* texture);
  void update_texture(vk::structure::Texture* texture);
  VkFormat find_texture_format(utl::media::Image* image);

  //Texture cleaning
  void clean_texture(vk::structure::Object* vk_object);
  void clean();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Memory* vk_memory;
  vk::command::Transfert* vk_transfert;
  vk::data::Buffer* vk_buffer;
  vk::image::Image* vk_image;
};

}
