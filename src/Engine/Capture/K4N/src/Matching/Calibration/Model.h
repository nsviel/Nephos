#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class K4N;}
namespace k4n::detection{class Hough;}
namespace k4n::matching{class Image;}
namespace k4n::detection{class Glyph;}


namespace k4n::calibration{

class Model
{
public:
  //Constructor / Destructor
  Model(k4n::Node* node_k4n);
  ~Model();

public:
  //Main function
  void determine_model(k4n::dev::Sensor* sensor);

  //Subfunction
  void retrieve_sphere_data(k4n::dev::Sensor* sensor);
  void retrieve_bbox_data(k4n::dev::Sensor* sensor);

private:
  k4n::dev::Swarm* k4n_swarm;
  k4n::structure::K4N* k4n_struct;
  k4n::detection::Hough* k4n_hough;
  k4n::matching::Image* k4n_image;
  k4n::detection::Glyph* k4n_glyph;
};

}
