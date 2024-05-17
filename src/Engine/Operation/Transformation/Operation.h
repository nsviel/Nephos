#pragma once

#include <glm/glm.hpp>

namespace ope{class Transformation;}
namespace ope::attribut{class Location;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace ope{

class Operation
{
public:
  // Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Operation on set
  void center_object(utl::base::Element* element);
  void elevate_object(utl::base::Element* element);
  void make_rotation_X_90d(utl::base::Element* element, int value);
  void make_translation(utl::base::Element* element, glm::vec3 value);
  void make_rotation(utl::base::Element* element, glm::vec3 value);

  //Operation on entity
  void center_object(dat::base::Entity* entity, glm::vec3 COM);
  void elevate_object(dat::base::Entity* entity, glm::vec3 min);
  void make_rotation_X_90d(dat::base::Entity* entity, int value);
  void make_translation_from_root(dat::base::Entity* entity, glm::vec3 new_root);

private:
  ope::Transformation* ope_transform;
  ope::attribut::Location* ope_location;
};

}
