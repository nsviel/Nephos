#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Plot;}
namespace dat::base{class Sensor;}


namespace rad::cor{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::cor::Node* node_correction);
  ~Measure();

public:
  //Main function
  void init();
  void process_measure(dat::base::Sensor& sensor);

  //Subfunction
  void data_measure(dat::base::Sensor& sensor, std::vector<glm::vec3>& sphere_xyz, std::vector<float>& sphere_i);
  void data_IfR(dat::base::Sensor& sensor, std::vector<glm::vec3>& sphere_xyz, std::vector<float>& sphere_i);
  void data_IfIt(std::vector<glm::vec3>& sphere_xyz, std::vector<float>& sphere_i);

private:
  rad::cor::Structure* rad_struct;
  rad::cor::Plot* rad_plot;
};

}
