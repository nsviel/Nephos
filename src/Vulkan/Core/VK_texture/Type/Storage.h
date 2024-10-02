#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace vk::data{class Retriever;}
namespace vk::image{class Format;}
namespace vk::image{class Image;}
namespace vk::memory{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk::memory{class Transition;}
namespace vk::instance{class UID;}
namespace vk::structure{class Object;}
namespace vk::structure{class Texture;}
namespace utl::base{class Storage;}
namespace utl::base{class Data;}


namespace vk::texture{

class Storage
{
public:
  //Constructor / Destructor
  Storage(vk::Structure* vk_struct);
  ~Storage();

public:
  //Main function
  void insert_storage(utl::base::Data& data, std::shared_ptr<utl::base::Storage> storage);
  void insert_storage_empty(utl::base::Data& data, std::shared_ptr<utl::base::Storage> storage);
  void update_storage(std::shared_ptr<utl::base::Storage> storage);

  //Subfunction
  std::shared_ptr<vk::structure::Texture> create_texture(std::shared_ptr<utl::base::Storage> storage);

private:
  vk::Structure* vk_struct;
  vk::texture::Ressource* vk_ressource;
  vk::data::Retriever* vk_retriever;
  vk::image::Format* vk_format;
  vk::memory::Allocator* vk_mem_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::memory::Transition* vk_transition;
  vk::image::Image* vk_image;
  vk::instance::UID* vk_uid;
};

}
