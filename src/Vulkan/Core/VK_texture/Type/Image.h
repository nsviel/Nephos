#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace vk::data{class Retriever;}
namespace vk::structure{class Object;}
namespace vk::structure{class Texture;}
namespace utl::base{class Image;}
namespace utl::base{class Data;}


namespace vk::texture{

class Image
{
public:
  //Constructor / Destructor
  Image(vk::Structure* vk_struct);
  ~Image();

public:
  //Main function
  void insert_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> image);
  void insert_image(vk::structure::Object& vk_object, std::shared_ptr<utl::base::Image> image);
  void insert_image(std::shared_ptr<utl::base::Image> image);
  void update_texture(std::shared_ptr<utl::base::Image> image);

  //Subfunction
  void clean_texture(vk::structure::Object& vk_object);

private:
  vk::Structure* vk_struct;
  vk::texture::Ressource* vk_ressource;
  vk::data::Retriever* vk_retriever;
};

}
