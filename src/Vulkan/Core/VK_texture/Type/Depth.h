#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace vk::data{class Retriever;}
namespace vk::image{class Format;}
namespace vk::image{class Ressource;}
namespace vk::memory{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk::memory{class Transition;}
namespace vk::instance{class UID;}
namespace vk::structure{class Object;}
namespace vk::structure{class Texture;}
namespace utl::base{class Depth;}
namespace utl::base{class Data;}


namespace vk::texture{

class Depth
{
public:
  //Constructor / Destructor
  Depth(vk::Structure* vk_struct);
  ~Depth();

public:
  //Main function
  void insert_depth(utl::base::Data& data, std::shared_ptr<utl::base::Depth> depth);
  void update_depth(utl::base::Data& data, std::shared_ptr<utl::base::Depth> depth);

  //Subfunction
  std::shared_ptr<vk::structure::Texture> create_texture(std::shared_ptr<utl::base::Depth> depth);

private:
  vk::Structure* vk_struct;
  vk::texture::Ressource* vk_ressource;
  vk::data::Retriever* vk_retriever;
  vk::image::Format* vk_format;
  vk::memory::Allocator* vk_mem_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::image::Ressource* vk_image;
  vk::instance::UID* vk_uid;
  vk::memory::Transition* vk_transition;
};

}
