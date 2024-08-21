#pragma once

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor::image{class Detection;}
namespace rad::cor::cloud{class Detection;}
namespace rad::cor{class Glyph;}
namespace dat::gph{class Selection;}
namespace dat::elm{class Image;}
namespace dat::base{class Sensor;}


namespace rad::cor{

class Process
{
public:
  //Constructor / Destructor
  Process(rad::cor::Node* node_correction);
  ~Process();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void step_detection();
  void step_measure();

private:
  rad::cor::Structure* rad_struct;
  rad::cor::image::Detection* rad_image_detection;
  rad::cor::cloud::Detection* rad_cloud_detection;
  rad::cor::Glyph* rad_glyph;
  dat::gph::Selection* gph_selection;
  dat::elm::Image* dat_image;
};

}
