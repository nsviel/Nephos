#pragma once

#include <Utility/Specific/common.h>

namespace vk::image{class Image;}
namespace vk::command{class Memory;}
namespace vk::command{class Transfert;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Texture;}
namespace vk::structure{class Object;}
namespace vk::data{class Buffer;}
namespace vk::instance{class UID;}


namespace vk::main{

class Texture
{
public:
  //Constructor / Destructor
  Texture(vk::structure::Vulkan* struct_vulkan);
  ~Texture();

public:
  //Main functions
  void clean();

  //Texture function
  void clean_texture(vk::structure::Object* vk_object);
  void update_texture(vk::structure::Texture* texture);
  VkFormat find_texture_format(utl::media::Image* image);
  vk::structure::Texture* load_texture(utl::media::Image* texture);
  vk::structure::Texture* find_texture(string name);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Memory* vk_memory;
  vk::command::Transfert* vk_transfert;
  vk::data::Buffer* vk_buffer;
  vk::image::Image* vk_image;
  vk::instance::UID* vk_uid;
};

}
