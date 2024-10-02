#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace vk::data{class Retriever;}
namespace vk::structure{class Object;}
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
  void insert_depth(vk::structure::Object& vk_object, std::shared_ptr<utl::base::Depth> depth);

private:
  vk::Structure* vk_struct;
  vk::texture::Ressource* vk_ressource;
  vk::data::Retriever* vk_retriever;
};

}
