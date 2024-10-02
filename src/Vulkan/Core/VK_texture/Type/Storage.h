#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace vk::data{class Retriever;}
namespace vk::structure{class Object;}
namespace utl::base{class Storage;}


namespace vk::texture{

class Storage
{
public:
  //Constructor / Destructor
  Storage(vk::Structure* vk_struct);
  ~Storage();

public:
  //Main function
  void insert_storage(vk::structure::Object& vk_object, std::shared_ptr<utl::base::Storage> storage);

private:
  vk::Structure* vk_struct;
  vk::texture::Ressource* vk_ressource;
  vk::data::Retriever* vk_retriever;
};

}
