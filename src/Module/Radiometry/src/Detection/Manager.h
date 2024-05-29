#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::detection::image{class Detection;}
namespace rad::detection::cloud{class Detection;}
namespace dat{class Graph;}
namespace ope::image{class Manager;}
namespace dat::base{class Sensor;}


namespace rad::detection{

enum Step{
  WAIT = 0,
  VALIDATION = 1,
  PROCESSING = 2,
};

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
  void next_correction_step();
  void next_calibration_step();

  inline rad::detection::image::Detection* get_image_detection(){return rad_image_detection;}
  inline rad::detection::cloud::Detection* get_cloud_detection(){return rad_cloud_detection;}
  inline int get_correction_step(){return correction_step;}
  inline int get_calibration_step(){return calibration_step;}

private:
  dat::Graph* dat_graph;
  ope::image::Manager* ope_image;
  rad::detection::image::Detection* rad_image_detection;
  rad::detection::cloud::Detection* rad_cloud_detection;

  int correction_step = 0;
  int calibration_step = 0;
};

}
