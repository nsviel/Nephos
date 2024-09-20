#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk::image{class Image;}
namespace vk::memory{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk{class Structure;}
namespace vk::structure{class Texture;}
namespace vk::structure{class Object;}
namespace vk::data{class Buffer;}
namespace vk::instance{class UID;}
namespace vk::image{class Screenshot;}
namespace vk::texture{class Ressource;}
namespace utl::media{class Image;}
namespace utl::base{class Data;}


namespace vk::texture{

class Data
{
public:
  //Constructor / Destructor
  Data(vk::Structure* vk_struct);
  ~Data();

public:
  //Main function
  void insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> utl_image);

  //Subfunction
  void clean_texture(vk::structure::Object& vk_object);

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::data::Buffer* vk_buffer;
  vk::image::Image* vk_image;
  vk::instance::UID* vk_uid;
  vk::image::Screenshot* vk_screenshot;
  vk::texture::Ressource* vk_ressource;
};

}
