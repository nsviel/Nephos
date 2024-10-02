#pragma once

#include <memory>
#include <string>

namespace vk{class Structure;}
namespace vk::structure{class Object;}
namespace vk::structure{class Texture;}
namespace utl::base{class Data;}
namespace utl::base{class Image;}


namespace vk::data{

class Retriever
{
public:
  //Constructor / Destructor
  Retriever(vk::Structure* vk_struct);
  ~Retriever();

public:
  //Main function
  std::shared_ptr<vk::structure::Object> retrieve_vk_object(utl::base::Data& data);
  std::shared_ptr<vk::structure::Texture> retrieve_vk_texture(utl::base::Image& image);
  std::shared_ptr<vk::structure::Texture> retrieve_vk_texture(vk::structure::Object& vk_object, std::string name);

private:
  vk::Structure* vk_struct;
};

}
