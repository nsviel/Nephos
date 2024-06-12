#pragma once

#include <Utility/Specific/Common.h>

namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::image{class Detection;}
namespace rad::detection::cloud{class Detection;}
namespace rad::detection::sphere{class Glyph;}
namespace dat{class Selection;}
namespace dat{class Image;}
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
  void step_detection();

private:
  rad::detection::Structure* rad_struct;
  rad::detection::image::Detection* rad_image_detection;
  rad::detection::cloud::Detection* rad_cloud_detection;
  rad::detection::sphere::Glyph* rad_glyph;
  dat::Selection* dat_selection;
  dat::Image* dat_image;
};

}
