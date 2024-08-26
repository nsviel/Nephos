#pragma once

#include <memory>

namespace rad{class Node;}
namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace dat::img::gui{class Stream;}
namespace dat::elm{class Image;}
namespace dat::base{class Sensor;}


namespace rad::cor::gui{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::Node* node_radio);
  ~Correction();

public:
  //Main function
  void draw_tab(std::shared_ptr<dat::base::Sensor> sensor);

  //Subfunction
  void display_image(std::shared_ptr<dat::base::Sensor> sensor);

private:
  rad::cor::Structure* rad_struct;
  dat::img::gui::Stream* stream_1;
  dat::img::gui::Stream* stream_2;
  dat::elm::Image* dat_image;
};

}
