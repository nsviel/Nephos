#pragma once

namespace rad{class Node;}
namespace rad::gui::correction{class Detection;}
namespace rad::gui::correction{class Model;}
namespace rad::gui::correction{class Correction;}
namespace dyn::prc::base{class Sensor;}


namespace rad::gui::correction{

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
  rad::gui::correction::Detection* gui_detection;
  rad::gui::correction::Model* gui_model;
  rad::gui::correction::Correction* gui_correction;
};

}
