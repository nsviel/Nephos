#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Base/Namespace.h>
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
  void make_translation(eng::structure::Object* object, vec3 trans);
  void make_translation(eng::structure::Object* object, mat4 translation);

  // Rotation
  void make_rotation(eng::structure::Object* object, vec3 COM, vec3 radian);
  void make_rotation(eng::structure::Object* object, vec3 degree);
  void make_rotation(eng::structure::Object* object, mat4 rotation);

  //Scaling
  void make_scaling(eng::structure::Object* object, float scale);

  //Subfunction
  mat4 get_translation_mat(vec3 trans);
  mat4 get_translation_mat_neye(vec3 trans);
  mat4 get_rotation_mat(vec3 radian);

private:
};

}
