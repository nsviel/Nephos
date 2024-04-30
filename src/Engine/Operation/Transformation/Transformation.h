#pragma once

#include <glm/glm.hpp>

namespace dat::base{class Entity;}
namespace utl::type{class Pose;}


namespace ope{

class Transformation
{
public:
  // Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  // Translation
  void make_translation(dat::base::Entity* entity, glm::vec3 trans);
  void make_translation(dat::base::Entity* entity, glm::mat4 translation);

  // Rotation
  void make_rotation(dat::base::Entity* entity, glm::vec3 COM, glm::vec3 degree);
  void make_rotation(dat::base::Entity* entity, glm::vec3 degree);
  void make_rotation(dat::base::Entity* entity, glm::vec3 COM, glm::mat4 rotation);
  void make_rotation_axe_X(dat::base::Entity* entity, float degree);

  //Scaling
  void make_scaling(dat::base::Entity* entity, float scale);

  //Transformation
  void make_transformation(utl::type::Pose* pose, glm::vec3 COM, glm::mat4 translation, glm::mat4 rotation);

  //Subfunction
  glm::mat4 get_translation_mat(glm::vec3 trans);
  glm::mat4 get_translation_mat_neye(glm::vec3 trans);
  glm::mat4 get_rotation_mat(glm::vec3 radian);

private:
};

}
