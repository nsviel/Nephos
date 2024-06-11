#pragma once

#include <Utility/Specific/Common.h>

namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::image{class Detection;}
namespace rad::detection::cloud{class Detection;}
namespace rad::detection::glyph{class Manager;}
namespace dat{class Selection;}
namespace dyn::base{class Sensor;}


namespace rad::detection::sphere{

class Process
{
public:
  //Constructor / Destructor
  Process(rad::detection::Node* node_detection);
  ~Process();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void step_sphere_detection();

private:
  rad::detection::Structure* rad_struct;
  rad::detection::image::Detection* rad_image_detection;
  rad::detection::cloud::Detection* rad_cloud_detection;
  rad::detection::glyph::Manager* rad_glyph;
  dat::Selection* dat_selection;
};

}
