#pragma once

#include <glm/glm.hpp>
#include <string>

namespace utl::base{class Pose;}


namespace eng::trf{

class Utils
{
public:
  // Constructor / Destructor
  Utils();
  ~Utils();

public:
  //Main function
  glm::mat4 get_translation_matrix(glm::vec3 trans);
  glm::mat4 get_rotation_matrix(glm::vec3 radian);
  glm::mat4 find_transformation_from_file(std::string path);
  glm::vec3 get_euler_angles(glm::mat4 rotation);
  glm::vec3 get_translation_from_matrix(const glm::mat4& matrix);
  void save_transformation_to_file(glm::mat4& mat, std::string path);
  void make_transformation_identity(glm::mat4& mat);
  void init_and_heighten_transformation(glm::mat4& mat, float value);

private:
};

}
