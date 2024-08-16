#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Measure;}
namespace rad::correction{class Glyph;}
namespace dyn::prc::base{class Sensor;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}


namespace rad::correction::cloud{

class Ransac
{
public:
  //Constructor / Destructor
  Ransac(rad::correction::Node* node_correction);
  ~Ransac();

public:
  //Main function
  void ransac_sphere(dyn::prc::base::Sensor* sensor);

  //Algo function
  void reset_search_space();
  void reduce_search_space(dyn::prc::base::Sensor* sensor);
  void apply_ransac();
  void apply_refinement();

  //Subfunction
  glm::vec3 project_point_on_plane(const glm::vec3& point, const glm::vec3& normal);
  int find_nearest_point(const std::vector<glm::vec3>& search_xyz, const glm::vec3& center_direction);

private:
  rad::correction::Measure* rad_measure;
  rad::correction::Structure* rad_struct;
  rad::correction::Glyph* rad_glyph;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
};

}
