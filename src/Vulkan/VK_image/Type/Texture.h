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


namespace vk::image{

class Texture
{
public:
  //Constructor / Destructor
  Texture(vk::Structure* vk_struct);
  ~Texture();

public:
  //Main function
  void clean();

  //Texture function
  void import_texture(std::shared_ptr<utl::media::Image> utl_image);
  void export_texture(std::shared_ptr<utl::media::Image> utl_image);
  void clean_texture(vk::structure::Texture* texture);

  //Texture subfunction
  void clean_texture(vk::structure::Object* vk_object);
  void update_texture(vk::structure::Texture* texture);
  void create_texture(vk::structure::Texture* texture);

  //Subfunction
  VkFormat find_texture_format(std::shared_ptr<utl::media::Image> image);
  vk::structure::Texture* query_texture(int UID);

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
