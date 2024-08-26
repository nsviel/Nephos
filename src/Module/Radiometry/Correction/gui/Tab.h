#pragma once

#include <memory>

namespace rad{class Node;}
namespace rad::cor::gui{class Detection;}
namespace rad::cor::gui{class Model;}
namespace rad::cor::gui{class Correction;}
namespace dat::base{class Sensor;}


namespace rad::cor::gui{

class Tab
{
public:
  //Constructor / Destructor
  Tab(rad::Node* node_radio);
  ~Tab();

public:
  //Main function
  void design_tab(std::shared_ptr<dat::base::Sensor> sensor);

  //Subfunction
  void tab_detection(std::shared_ptr<dat::base::Sensor> sensor);
  void tab_modeld(std::shared_ptr<dat::base::Sensor> sensor);
  void tab_calibration(std::shared_ptr<dat::base::Sensor> sensor);

private:
  rad::cor::gui::Detection* gui_detection;
  rad::cor::gui::Model* gui_model;
  rad::cor::gui::Correction* gui_correction;
};

}
