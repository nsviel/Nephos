#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace dat::img{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace vk::interface{class Data;}
namespace utl::base{class Image;}


namespace dat::img{

class Image
{
public:
  //Constructor / Destructor
  Image(dat::img::Node* node_image);
  ~Image();

public:
  //Main function
  void add_image(dat::base::Entity& entityy, std::shared_ptr<utl::base::Image> image);

  //Subfunction
  void insert_image(dat::base::Entity& entity, std::shared_ptr<utl::base::Image> image);
  std::shared_ptr<utl::base::Image> get_image(dat::base::Entity& entity, std::string name);
  std::shared_ptr<utl::base::Image> get_or_create_image(dat::base::Entity& entity, std::string name);

private:
  vk::interface::Data* vk_data;
  dat::elm::UID* dat_uid;
};

}
