#pragma once

namespace rad{class Node;}
namespace rad::cal::gui{class Detection;}
namespace dyn::prc::base{class Sensor;}


namespace rad::cal::gui{

class Tab
{
public:
  //Constructor / Destructor
  Tab(rad::Node* node_radio);
  ~Tab();

public:
  //Main function
  void design_tab(dyn::prc::base::Sensor* sensor);

  //Subfunction
  void tab_detection(dyn::prc::base::Sensor* sensor);
  void tab_modeld(dyn::prc::base::Sensor* sensor);
  void tab_calibration(dyn::prc::base::Sensor* sensor);

private:
  rad::cal::gui::Detection* gui_detection;
};

}
