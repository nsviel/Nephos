#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}
namespace utl::base{class Attribut;}


namespace ope::attribut{

class Attribut
{
public:
  // Constructor / Destructor
  Attribut();
  ~Attribut();

public:
  //Main function
  void compute_range(dat::base::Entity* entity);
  void compute_incidence_angle(dat::base::Entity* entity);
  void set_unicolor(dat::base::Entity* entity);

private:
  utl::base::Attribut* utl_attribut;
};

}
