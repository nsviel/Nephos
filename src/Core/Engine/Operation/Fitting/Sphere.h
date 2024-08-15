#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::media{class Image;}


namespace ope::fitting{

class Sphere
{
public:
  Sphere();
  ~Sphere();

public:
  //Sphere fitting
  void find_sphere_in_cloud(std::vector<glm::vec3>& xyz, glm::vec3& center, float& radius);
  void find_sphere_in_cloud_with_known_radius(std::vector<glm::vec3>& xyz, glm::vec3& center, float known_radius);
  void find_circle_in_image(utl::media::Image* image);
  void find_circle_in_image_with_canny(utl::media::Image* image);

private:
};

}
