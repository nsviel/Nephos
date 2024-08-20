#pragma once

namespace rad{class Node;}
namespace rad::cal::gui{class Detection;}
namespace dat::base{class Sensor;}


namespace rad::cal::gui{

class Tab
{
public:
  //Constructor / Destructor
  Tab(rad::Node* node_radio);
  ~Tab();

public:
  //Main function
  void design_tab(dat::base::Sensor* sensor);

  //Subfunction
  void tab_detection(dat::base::Sensor* sensor);
  void tab_modeld(dat::base::Sensor* sensor);
  void tab_calibration(dat::base::Sensor* sensor);

private:
  rad::cal::gui::Detection* gui_detection;
};

}
