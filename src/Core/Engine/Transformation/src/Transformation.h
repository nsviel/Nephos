#pragma once

#include <glm/glm.hpp>

namespace utl::base{class Pose;}
namespace eng::trf{class Utils;}


namespace eng::trf{

class Transformation
{
public:
  // Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  // Translation
  void make_translation(utl::base::Pose* pose, glm::vec3 trans);
  void make_translation(utl::base::Pose* pose, glm::mat4 translation);

  // Rotation
  void make_rotation(utl::base::Pose* pose, glm::vec3 COM, glm::vec3 degree);
  void make_rotation(utl::base::Pose* pose, glm::vec3 degree);
  void make_rotation(utl::base::Pose* pose, glm::vec3 COM, glm::mat4 rotation);
  void make_rotation_axe_X(utl::base::Pose* pose, float degree);

  //Scaling
  void make_scaling(utl::base::Pose* pose, float scale);

  //Transformation
  void make_transformation(utl::base::Pose* pose, glm::vec3 COM, glm::mat4 translation, glm::mat4 rotation);

private:
  eng::trf::Utils* trf_utils;
};

}
