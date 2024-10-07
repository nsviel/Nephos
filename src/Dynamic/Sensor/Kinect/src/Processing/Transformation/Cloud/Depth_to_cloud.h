#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace k4n{class Node;}
namespace k4n{class Structure;}


namespace k4n::transformation{

class Depth_to_cloud
{
public:
  //Constructor / Destructor
  Depth_to_cloud(k4n::Node* node_k4n);
  ~Depth_to_cloud();

public:
  //Main function
  void make_transformation(k4n::base::Sensor& sensor);

  //Subfunction
  void create_cloud_image(k4n::base::Sensor& sensor);
  void transform_to_cloud(k4n::base::Sensor& sensor);

private:
  k4n::Structure* k4n_struct;
};

}
