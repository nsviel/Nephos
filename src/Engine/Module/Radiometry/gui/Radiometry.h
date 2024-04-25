#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Swarm;}
namespace radio{class Structure;}
namespace radio::gui{class Detection;}
namespace radio::gui{class Calibration;}


namespace radio::gui{

class Radiometry
{
public:
  //Constructor / Destructor
  Radiometry(radio::Structure* radio_struct, bool* show_window);
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
  radio::Structure* radio_struct;
  radio::gui::Detection* gui_detection;
  radio::gui::Calibration* gui_calibration;

  string name;
  bool* show_window;
};

}
