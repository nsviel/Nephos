#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
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

class Manager
{
public:
  //Constructor / Destructor
  Manager(rad::Node* node_radio);
  ~Manager();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void step_sphere_detection();
  void step_chart_detection();

  inline rad::detection::image::Detection* get_image_detection(){return rad_image_detection;}
  inline rad::detection::cloud::Detection* get_cloud_detection(){return rad_cloud_detection;}

private:
  rad::Structure* rad_struct;
  rad::detection::image::Detection* rad_image_detection;
  rad::detection::cloud::Detection* rad_cloud_detection;
  rad::detection::glyph::Manager* rad_glyph;
  dat::Selection* dat_selection;
};

}
