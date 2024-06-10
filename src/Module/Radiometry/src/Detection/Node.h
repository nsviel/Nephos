#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::image{class Detection;}
namespace rad::detection::cloud{class Detection;}
namespace rad::detection::glyph{class Manager;}
namespace dat{class Selection;}
namespace dyn::base{class Sensor;}


namespace rad::detection{

enum Step{
  VALIDATION = 1,
  PROCESSING = 2,
};

enum Data{
  NO_DATA = 0,
  HAS_DATA = 3,
};

class Node
{
public:
  //Constructor / Destructor
  Node(rad::Node* node_radio);
  ~Node();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void step_sphere_detection();
  void step_chart_detection();

  inline rad::Node* get_node_radio(){return node_radio;}
  inline rad::detection::Structure* get_rad_struct(){return rad_struct;}
  inline rad::detection::image::Detection* get_image_detection(){return rad_image_detection;}
  inline rad::detection::cloud::Detection* get_cloud_detection(){return rad_cloud_detection;}

private:
  rad::Node* node_radio;
  rad::detection::Structure* rad_struct;
  rad::detection::image::Detection* rad_image_detection;
  rad::detection::cloud::Detection* rad_cloud_detection;
  rad::detection::glyph::Manager* rad_glyph;
  dat::Selection* dat_selection;
};

}