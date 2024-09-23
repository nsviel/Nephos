#pragma once

#include <memory>
#include <string>

namespace vk{class Structure;}
namespace vk::structure{class Object;}
namespace vk::structure{class Texture;}
namespace utl::base{class Data;}
namespace utl::media{class Image;}


namespace vk::data{

class Function
{
public:
  //Constructor / Destructor
  Function(vk::Structure* vk_struct);
  ~Function();

public:
  //Main function
  std::shared_ptr<vk::structure::Object> retrieve_vk_object(utl::base::Data& data);
  std::shared_ptr<vk::structure::Texture> retrieve_vk_texture(utl::media::Image& image);
  std::shared_ptr<vk::structure::Texture> retrieve_vk_texture(vk::structure::Object& vk_object, std::string name);

private:
  vk::Structure* vk_struct;
};

}
