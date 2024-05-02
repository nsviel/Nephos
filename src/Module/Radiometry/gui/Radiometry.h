#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Master;}
namespace dat::base{class Sensor;}
namespace k4n::dev{class Swarm;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::gui{class Detection;}
namespace rad::gui{class Calibration;}


namespace rad::gui{

class Radiometry
{
public:
  //Constructor / Destructor
  Radiometry(rad::Node* node_radio, bool* show_window);
  ~Radiometry();

public:
  //Main function
  void run_panel();
  void design_panel(k4n::dev::Master* master);

  //Subfunction
  void matching_parameter(dat::base::Sensor* sensor);
  void tab_detection(dat::base::Sensor* sensor);
  void tab_calibration(dat::base::Sensor* sensor);

private:
  k4n::dev::Swarm* k4n_swarm;
  rad::Structure* radio_struct;
  rad::gui::Detection* gui_detection;
  rad::gui::Calibration* gui_calibration;

  string name;
  bool* show_window;
};

}
