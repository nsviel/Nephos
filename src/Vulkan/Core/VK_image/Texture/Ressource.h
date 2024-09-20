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
namespace utl::media{class Image;}
namespace utl::base{class Data;}


namespace vk::texture{

class Ressource
{
public:
  //Constructor / Destructor
  Ressource(vk::Structure* vk_struct);
  ~Ressource();

public:
  //Main function
  void clean();

  //Texture function
  void insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> utl_image);
  void insert_texture(std::shared_ptr<utl::media::Image> utl_image);
  void export_texture(std::shared_ptr<utl::media::Image> utl_image);
  void clean_texture(std::shared_ptr<vk::structure::Texture> texture);

  //Texture subfunction
  void clean_texture(vk::structure::Object& vk_object);
  void update_texture(std::shared_ptr<vk::structure::Texture> texture);
  void create_texture(std::shared_ptr<vk::structure::Texture> texture);

  //Subfunction
  VkFormat find_texture_format(std::shared_ptr<utl::media::Image> image);
  std::shared_ptr<vk::structure::Texture> query_texture(int UID);

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::data::Buffer* vk_buffer;
  vk::image::Image* vk_image;
  vk::instance::UID* vk_uid;
  vk::image::Screenshot* vk_screenshot;
};

}
