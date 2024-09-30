#pragma once

#include <Kinect/src/Structure/Configuration/Transformation.h>
#include <Thread/Task/Job.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}


namespace k4n::processing{

class Table_xy : public thr::Job
{
public:
  //Constructor / Destructor
  Table_xy(k4n::Node* node_k4n);
  ~Table_xy();

public:
  //Main function
  void thread_function();

  //Subfunction
  void build_texture(k4n::base::Sensor& sensor, k4a_calibration_type_t calibration);
  void table_color_to_depth(k4n::base::Sensor& sensor);
  void apply_map(k4n::base::Sensor& sensor, int i);

private:
  k4n::Structure* k4n_struct;

  k4n::transformation::cmap map_xy;
};

}
