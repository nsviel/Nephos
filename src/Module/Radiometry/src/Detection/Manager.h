#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::detection::image{class Detection;}
namespace rad::detection::cloud{class Detection;}
namespace dat{class Graph;}
namespace ope::image{class Manager;}
namespace dat::base{class Sensor;}


namespace rad::detection{

class Manager
{
public:
  //Constructor / Destructor
  Manager(rad::Node* node_radio);
  ~Manager();

public:
  //Main function
  void loop();

  //Subfunction
  void next_step(dat::base::Sensor* sensor);

  inline rad::detection::image::Detection* get_image_detection(){return rad_image_detection;}
  inline rad::detection::cloud::Detection* get_cloud_detection(){return rad_cloud_detection;}

  inline string get_step_str(){return map_step[step];}
  inline int get_step(){return step;}

private:
  dat::Graph* dat_graph;
  ope::image::Manager* ope_image;
  rad::detection::image::Detection* rad_image_detection;
  rad::detection::cloud::Detection* rad_cloud_detection;

  std::map<int, std::string> map_step;
  int step = 0;
};

}
