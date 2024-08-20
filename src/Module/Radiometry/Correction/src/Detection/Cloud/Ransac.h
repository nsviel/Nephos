#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Measure;}
namespace rad::cor{class Glyph;}
namespace dat::base{class Sensor;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}


namespace rad::cor::cloud{

class Ransac
{
public:
  //Constructor / Destructor
  Ransac(rad::cor::Node* node_correction);
  ~Ransac();

public:
  //Main function
  void ransac_sphere(dat::base::Sensor* sensor);

  //Algo function
  void reset_search_space();
  void reduce_search_space(dat::base::Sensor* sensor);
  void apply_ransac();
  void apply_refinement();

  //Subfunction
  glm::vec3 project_point_on_plane(const glm::vec3& point, const glm::vec3& normal);
  int find_nearest_point(const std::vector<glm::vec3>& search_xyz, const glm::vec3& center_direction);

private:
  rad::cor::Measure* rad_measure;
  rad::cor::Structure* rad_struct;
  rad::cor::Glyph* rad_glyph;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
};

}
