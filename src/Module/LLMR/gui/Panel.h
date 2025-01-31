#pragma once

#include <memory>
#include <string>

namespace llmr{class Node;}
namespace dat::gph{class Selection;}
namespace dat::base{class Sensor;}


namespace llmr::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(llmr::Node* node_llmr, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel(dat::base::Sensor& sensor);

  //Subfunction
  void tab_correction(dat::base::Sensor& sensor);
  void tab_calibration(dat::base::Sensor& sensor);

private:
  dat::gph::Selection* gph_selection;

  std::string name;
  bool* show_window;
};

}
