#pragma once

#include <Utility/Specific/Common.h>

namespace ope{class Transformation;}
namespace ope::attribut{class Location;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace ope{

class Operation
{
public:
  // Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Operation on set
  void center_object(dat::base::Set* set);
  void elevate_object(dat::base::Set* set);
  void make_rotation_X_90d(dat::base::Set* set, int value);
  void make_translation(dat::base::Set* set, vec3 value);
  void make_rotation(dat::base::Set* set, vec3 value);

  //Operation on entity
  void center_object(dat::base::Entity* entity, vec3 COM);
  void elevate_object(dat::base::Entity* entity, vec3 min);
  void make_rotation_X_90d(dat::base::Entity* entity, int value);
  void make_translation_from_root(dat::base::Entity* entity, vec3 new_root);

private:
  ope::Transformation* ope_transform;
  ope::attribut::Location* ope_location;
};

}
