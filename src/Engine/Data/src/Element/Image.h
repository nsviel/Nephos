#pragma once

#include <glm/glm.hpp>
#include <string>

namespace dat{class Node;}
namespace dat{class UID;}
namespace dat::base{class Entity;}
namespace utl::media{class Image;}


namespace dat{

class Image
{
public:
  //Constructor / Destructor
  Image(dat::Node* node_data);
  ~Image();

public:
  //Main function
  void add_image(dat::base::Entity* entity, utl::media::Image* image);
  bool has_image(dat::base::Entity* entity, int type);

  //Subfunction
  void manage_UID(utl::media::Image* image);
  utl::media::Image* get_image(dat::base::Entity* entity, int type);
  utl::media::Image* get_or_create_image(dat::base::Entity* entity, int type);

private:
  dat::UID* dat_uid;
};

}
