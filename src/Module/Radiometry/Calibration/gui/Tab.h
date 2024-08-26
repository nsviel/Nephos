#pragma once

#include <memory>

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
  void design_tab(std::shared_ptr<dat::base::Sensor> sensor);

  //Subfunction
  void tab_detection(std::shared_ptr<dat::base::Sensor> sensor);
  void tab_modeld(std::shared_ptr<dat::base::Sensor> sensor);
  void tab_calibration(std::shared_ptr<dat::base::Sensor> sensor);

private:
  rad::cal::gui::Detection* gui_detection;
};

}
