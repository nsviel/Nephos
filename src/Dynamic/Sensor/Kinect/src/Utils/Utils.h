#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Set;}


namespace k4n{

class Utils
{
public:
  //Constructor / Destructor
  Utils(k4n::Node* node_k4n);
  ~Utils();

public:
  //Main function
  void insert_in_kinect_set(k4n::base::Sensor& sensor);
  glm::vec3 convert_depth_2d_to_3d(k4n::base::Sensor& sensor, glm::ivec2 point_2d);

private:
  dat::elm::Set* dat_set;
  dat::gph::Graph* dat_graph;
};

}
