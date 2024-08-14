#pragma once

namespace rad{class Node;}
namespace rad::gui::calibration{class Detection;}
namespace dyn::base{class Sensor;}


namespace rad::gui::calibration{

class Tab
{
public:
  //Constructor / Destructor
  Tab(rad::Node* node_radio);
  ~Tab();

public:
  //Main function
  void design_tab(dyn::base::Sensor* sensor);

  //Subfunction
  void tab_detection(dyn::base::Sensor* sensor);
  void tab_modeld(dyn::base::Sensor* sensor);
  void tab_calibration(dyn::base::Sensor* sensor);

private:
  rad::gui::calibration::Detection* gui_detection;
};

}
