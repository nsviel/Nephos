#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace dat::img{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
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
  void manage_UID(std::shared_ptr<utl::media::Image> image);

  //Subfunction
  bool is_image_inserted(dat::base::Entity& entity, int UID);
  std::shared_ptr<utl::media::Image> get_image(dat::base::Entity& entity, std::string name);
  std::shared_ptr<utl::media::Image> get_or_create_image(dat::base::Entity& entity, std::string name);

private:
  dat::elm::UID* dat_uid;
};

}
