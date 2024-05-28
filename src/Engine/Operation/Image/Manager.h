#pragma once

#include <glm/glm.hpp>
#include <string>

namespace dat::base{class Entity;}
namespace utl::media{class Image;}


namespace ope::image{

class Manager
{
public:
  //Constructor / Destructor
  Manager();
  ~Manager();

public:
  //Main function
  void add_image(dat::base::Entity* entity, utl::media::Image* image);
  bool has_image(dat::base::Entity* entity, int type);
  utl::media::Image* get_image(dat::base::Entity* entity, int type);
  utl::media::Image* get_or_create_image(dat::base::Entity* entity, int type);

private:

};

}
