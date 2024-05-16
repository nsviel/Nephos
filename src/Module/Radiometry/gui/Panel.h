#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Master;}
namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::gui{class Detection;}
namespace rad::gui{class Calibration;}


namespace rad::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(rad::Node* node_radio, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void matching_parameter(dat::base::Sensor* sensor);
  void tab_detection(dat::base::Sensor* sensor);
  void tab_calibration(dat::base::Sensor* sensor);

private:
  rad::Structure* radio_struct;
  rad::gui::Detection* gui_detection;
  rad::gui::Calibration* gui_calibration;

  string name;
  bool* show_window;
};

}
