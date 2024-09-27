#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Texture;}
namespace vk::image{class Screenshot;}
namespace vk::image{class Image;}
namespace vk::memory{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk::data{class Buffer;}
namespace vk::texture{class Format;}


namespace vk::texture{

class Ressource
{
public:
  //Constructor / Destructor
  Ressource(vk::Structure* vk_struct);
  ~Ressource();

public:
  //Main function
  void create_texture(vk::structure::Texture& texture);
  void update_texture(vk::structure::Texture& texture);
  void export_texture(vk::structure::Texture& texture);
  void clean_texture(vk::structure::Texture& texture);

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::image::Image* vk_image;
  vk::image::Screenshot* vk_screenshot;
  vk::texture::Format* vk_format;
  vk::data::Buffer* vk_buffer;
};

}