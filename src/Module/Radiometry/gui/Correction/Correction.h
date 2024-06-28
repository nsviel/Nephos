#pragma once

namespace rad{class Node;}
namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rnd{class Stream;}
namespace dat::element{class Image;}
namespace dyn::base{class Sensor;}


namespace rad::gui::correction{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::Node* node_radio);
  ~Correction();

public:
  //Main function
  void draw_tab(dyn::base::Sensor* sensor);

  //Subfunction
  void display_image(dyn::base::Sensor* sensor);

private:
  rad::correction::Structure* rad_struct;
  rnd::Stream* stream_1;
  rnd::Stream* stream_2;
  dat::element::Image* dat_image;
};

}
