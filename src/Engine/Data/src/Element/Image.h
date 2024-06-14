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
  void manage_UID(utl::media::Image* image);

  //Subfunction
  bool has_image_type(dat::base::Entity* entity, int type);
  bool has_image_UID(dat::base::Entity* entity, int UID);
  utl::media::Image* get_image(dat::base::Entity* entity, int type);
  utl::media::Image* get_or_create_image(dat::base::Entity* entity, int type);
  utl::media::Image* get_or_create_image(dat::base::Entity* entity, std::string name);

private:
  dat::UID* dat_uid;
};

}