#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace vk::structure{class Object;}
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
  vk::texture::Ressource* vk_ressource;
};

}
