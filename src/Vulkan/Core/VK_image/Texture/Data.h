#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace vk::data{class Function;}
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
  void insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> image);
  void insert_texture(std::shared_ptr<utl::media::Image> image);
  void update_texture(std::shared_ptr<utl::media::Image> image);

  //Subfunction
  void create_texture(vk::structure::Object& vk_object, std::shared_ptr<utl::media::Image> image);
  void clean_texture(vk::structure::Object& vk_object);
  bool check_image(std::shared_ptr<utl::media::Image> image);

private:
  vk::Structure* vk_struct;
  vk::texture::Ressource* vk_ressource;
  vk::data::Function* vk_data;
};

}
