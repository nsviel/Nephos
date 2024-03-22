#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Swarm;}
namespace k4n::structure{class K4N;}
namespace k4n::gui{class Detection;}
namespace k4n::gui{class Calibration;}


namespace k4n::gui{

class Matching
{
public:
  //Constructor / Destructor
  Matching(k4n::Node* node_k4n, bool* show_window);
  ~Matching();

public:
  //Main function
  void run_panel();
  void design_panel(k4n::dev::Master* master);

  //Subfunction
  void tab_detection(k4n::dev::Sensor* sensor);
  void tab_calibration(k4n::dev::Sensor* sensor);
  void tab_registration(k4n::dev::Sensor* sensor);
  void sensor_parameter(k4n::dev::Sensor* sensor);
  
private:
  k4n::dev::Swarm* k4n_swarm;
  k4n::structure::K4N* k4n_struct;
  k4n::gui::Detection* gui_detection;
  k4n::gui::Calibration* gui_calibration;

  string name;
  bool* show_window;
};

}
