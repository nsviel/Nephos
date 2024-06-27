#pragma once

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction::image{class Detection;}
namespace rad::correction::cloud{class Detection;}
namespace rad::correction{class Glyph;}
namespace dat{class Selection;}
namespace dat{class Image;}
namespace dyn::base{class Sensor;}


namespace rad::correction{

class Process
{
public:
  //Constructor / Destructor
  Process(rad::correction::Node* node_correction);
  ~Process();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void step_detection();
  void step_measure();

private:
  rad::correction::Structure* rad_struct;
  rad::correction::image::Detection* rad_image_detection;
  rad::correction::cloud::Detection* rad_cloud_detection;
  rad::correction::Glyph* rad_glyph;
  dat::Selection* dat_selection;
  dat::Image* dat_image;
};

}
