#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace dat::img{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace vk::interface{class Data;}
namespace utl::media{class Image;}


namespace dat::img{

class Image
{
public:
  //Constructor / Destructor
  Image(dat::img::Node* node_image);
  ~Image();

public:
  //Main function
  void add_image(dat::base::Entity& entityy, std::shared_ptr<utl::media::Image> image);

  //Subfunction
  std::shared_ptr<utl::media::Image> get_image(dat::base::Entity& entity, std::string name);
  std::shared_ptr<utl::media::Image> get_or_create_image(dat::base::Entity& entity, std::string name);

private:
  vk::interface::Data* vk_data;
  dat::elm::UID* dat_uid;
};

}
