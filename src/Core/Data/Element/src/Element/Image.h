#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace utl::media{class Image;}


namespace dat::elm{

class Image
{
public:
  //Constructor / Destructor
  Image(dat::elm::Node* node_element);
  ~Image();

public:
  //Main function
  void add_image(dat::base::Entity& entityy, std::shared_ptr<utl::media::Image> image);
  void manage_UID(std::shared_ptr<utl::media::Image> image);

  //Subfunction
  bool has_image_UID(dat::base::Entity& entity, int UID);
  std::shared_ptr<utl::media::Image> get_image(dat::base::Entity& entity, std::string name);
  std::shared_ptr<utl::media::Image> get_or_create_image(dat::base::Entity& entity, std::string name);

private:
  dat::elm::UID* dat_uid;
};

}
