#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Entity;}


namespace ope{

class Transformation
{
public:
  // Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  // Translation
  void make_translation(dat::base::Entity* entity, vec3 trans);
  void make_translation(dat::base::Entity* entity, mat4 translation);

  // Rotation
  void make_rotation(dat::base::Entity* entity, vec3 COM, vec3 degree);
  void make_rotation(dat::base::Entity* entity, vec3 degree);
  void make_rotation(dat::base::Entity* entity, vec3 COM, mat4 rotation);
  void make_rotation_axe_X(dat::base::Entity* entity, float degree);

  //Scaling
  void make_scaling(dat::base::Entity* entity, float scale);

  //Transformation
  void make_transformation(utl::type::Pose* pose, vec3 COM, mat4 translation, mat4 rotation);

  //Subfunction
  mat4 get_translation_mat(vec3 trans);
  mat4 get_translation_mat_neye(vec3 trans);
  mat4 get_rotation_mat(vec3 radian);

private:
};

}
