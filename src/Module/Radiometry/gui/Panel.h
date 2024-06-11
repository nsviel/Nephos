#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Selection;}
namespace rad{class Node;}
namespace rad::gui{class Detection;}
namespace rad::gui{class Model;}
namespace rad::gui{class Correction;}


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
  void matching_parameter();
  void tab_detection();
  void tab_modeld();
  void tab_calibration();

private:
  dat::Selection* dat_selection;
  rad::gui::Detection* gui_detection;
  rad::gui::Model* gui_model;
  rad::gui::Correction* gui_correction;

  string name;
  bool* show_window;
};

}
