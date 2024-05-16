#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Master;}
namespace dat::base{class Entity;}
namespace dat{class Graph;}
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
  void design_panel(dat::base::Entity* entity);

  //Subfunction
  void matching_parameter(dat::base::Entity* entity);
  void tab_detection(dat::base::Entity* entity);
  void tab_calibration(dat::base::Entity* entity);

private:
  dat::Graph* dat_graph;
  rad::Structure* rad_struct;
  rad::gui::Detection* gui_detection;
  rad::gui::Calibration* gui_calibration;

  string name;
  bool* show_window;
};

}