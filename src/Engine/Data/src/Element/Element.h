#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace utl::base{class Element;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dat{

class Element
{
public:
  Element();
  ~Element();

public:
  //Main function
  dat::base::Entity* get_active_entity(utl::base::Element* element);

private:
};

}
