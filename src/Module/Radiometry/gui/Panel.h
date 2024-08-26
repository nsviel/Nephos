#pragma once

#include <memory>
#include <string>

namespace dat::gph{class Selection;}
namespace rad{class Node;}
namespace rad::cor::gui{class Tab;}
namespace rad::cal::gui{class Tab;}
namespace dat::base{class Sensor;}


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
  void design_panel(std::shared_ptr<dat::base::Sensor> sensor);

  //Subfunction
  void tab_correction(std::shared_ptr<dat::base::Sensor> sensor);
  void tab_calibration(std::shared_ptr<dat::base::Sensor> sensor);

private:
  dat::gph::Selection* gph_selection;
  rad::cor::gui::Tab* gui_correction;
  rad::cal::gui::Tab* gui_calibration;

  std::string name;
  bool* show_window;
};

}
