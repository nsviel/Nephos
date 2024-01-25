#pragma once

#include <Utility/Specific/common.h>

namespace eng::ope{class Transformation;}
namespace eng::ope{class Attribut;}


namespace eng::ope{

class Operation
{
public:
  // Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Operation on set
  void center_object(utl::type::Set* set);
  void elevate_object(utl::type::Set* set);
  void make_rotation_X_90d(utl::type::Set* set, int value);
  void make_translation(utl::type::Set* set, vec3 value);
  void make_rotation(utl::type::Set* set, vec3 value);

  //Operation on entity
  void center_object(utl::type::Entity* entity, vec3 COM);
  void elevate_object(utl::type::Entity* entity, vec3 min);
  void make_rotation_X_90d(utl::type::Entity* entity, int value);

private:
  eng::ope::Transformation* ope_transform;
  eng::ope::Attribut* ope_attribut;
};

}
