#pragma once

#include <string>

namespace dat{class Selection;}
namespace rad{class Node;}
namespace rad::gui::correction{class Tab;}
namespace rad::gui::calibration{class Tab;}
namespace dyn::base{class Sensor;}


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
  void design_panel(dyn::base::Sensor* sensor);

  //Subfunction
  void tab_correction(dyn::base::Sensor* sensor);
  void tab_calibration(dyn::base::Sensor* sensor);

private:
  dat::Selection* dat_selection;
  rad::gui::correction::Tab* gui_correction;
  rad::gui::calibration::Tab* gui_calibration;

  std::string name;
  bool* show_window;
};

}
