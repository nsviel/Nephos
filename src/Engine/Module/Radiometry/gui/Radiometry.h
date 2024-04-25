#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Swarm;}
namespace k4n::structure{class K4N;}
namespace radio::gui{class Detection;}
namespace radio::gui{class Calibration;}


namespace radio::gui{

class Radiometry
{
public:
  //Constructor / Destructor
  Radiometry(k4n::Node* node_k4n, bool* show_window);
  ~Radiometry();

public:
  //Main function
  void run_panel();
  void design_panel(k4n::dev::Master* master);

  //Subfunction
  void matching_parameter(k4n::dev::Sensor* sensor);
  void tab_detection(k4n::dev::Sensor* sensor);
  void tab_calibration(k4n::dev::Sensor* sensor);

private:
  k4n::dev::Swarm* k4n_swarm;
  k4n::structure::K4N* k4n_struct;
  radio::gui::Detection* gui_detection;
  radio::gui::Calibration* gui_calibration;

  string name;
  bool* show_window;
};

}
