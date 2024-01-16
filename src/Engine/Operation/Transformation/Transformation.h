#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/Namespace.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;


namespace eng::ope{

class Transformation
{
public:
  // Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  // Translation
  void make_translation(utl::base::Data* data, vec3 trans);
  void make_translation(utl::base::Data* data, mat4 translation);

  // Rotation
  void make_rotation(utl::base::Data* data, vec3 COM, vec3 radian);
  void make_rotation(utl::base::Data* data, vec3 degree);
  void make_rotation(utl::base::Data* data, vec3 COM, mat4 rotation);
  void make_rotation_axe_X(utl::base::Data* data, float degree);

  //Scaling
  void make_scaling(utl::base::Data* data, float scale);

  //Transformation
  void make_transformation(utl::base::Data* data, vec3 COM, mat4 translation, mat4 rotation);

  //Subfunction
  mat4 get_translation_mat(vec3 trans);
  mat4 get_translation_mat_neye(vec3 trans);
  mat4 get_rotation_mat(vec3 radian);

private:
};

}
