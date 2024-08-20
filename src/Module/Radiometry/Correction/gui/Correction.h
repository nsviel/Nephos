#pragma once

namespace rad{class Node;}
namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rnd::gui{class Stream;}
namespace dat::elm{class Image;}
namespace dyn::prc::base{class Sensor;}


namespace rad::cor::gui{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::Node* node_radio);
  ~Correction();

public:
  //Main function
  void draw_tab(dyn::prc::base::Sensor* sensor);

  //Subfunction
  void display_image(dyn::prc::base::Sensor* sensor);

private:
  rad::cor::Structure* rad_struct;
  rnd::gui::Stream* stream_1;
  rnd::gui::Stream* stream_2;
  dat::elm::Image* dat_image;
};

}
