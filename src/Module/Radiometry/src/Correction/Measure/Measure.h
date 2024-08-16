#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Plot;}
namespace dyn::prc::base{class Sensor;}


namespace rad::correction{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::correction::Node* node_correction);
  ~Measure();

public:
  //Main function
  void init();
  void process_measure(dyn::base::Sensor* sensor);

  //Subfunction
  void data_measure(dyn::base::Sensor* sensor, std::vector<glm::vec3>& sphere_xyz, std::vector<float>& sphere_i);
  void data_IfR(dyn::base::Sensor* sensor, std::vector<glm::vec3>& sphere_xyz, std::vector<float>& sphere_i);
  void data_IfIt(std::vector<glm::vec3>& sphere_xyz, std::vector<float>& sphere_i);

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Plot* rad_plot;
};

}
