#pragma once

#include <Kinect/src/Structure/Configuration/Transformation.h>
#include <Thread/Task/Job.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace utl::base{class Image;}
namespace dat::img{class Image;}


namespace k4n::processing{

class Table_xy : public thr::Job
{
public:
  //Constructor / Destructor
  Table_xy(k4n::Node* node_k4n);
  ~Table_xy();

public:
  //Main function
  void build_table_xy(k4n::base::Sensor& sensor);

  //Subfunction
  void build_color_texture(k4n::base::Sensor& sensor);
  void build_depth_texture(k4n::base::Sensor& sensor);
  void build_texture(k4n::base::Sensor& sensor, utl::base::Image& image, k4a_calibration_type_t calibration);

private:
  k4n::Structure* k4n_struct;
  dat::img::Image* dat_image;
};

}
