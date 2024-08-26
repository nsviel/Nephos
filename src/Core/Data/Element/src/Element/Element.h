#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

namespace utl::base{class Element;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dat::elm{

class Element
{
public:
  Element();
  ~Element();

public:
  //Main function
  std::shared_ptr<dat::base::Entity> get_active_entity(std::shared_ptr<utl::base::Element> element);

private:
};

}
