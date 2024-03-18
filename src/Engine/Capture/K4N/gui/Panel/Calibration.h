#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}


namespace k4n::gui{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(k4n::Node* node_k4n, bool* show_window);
  ~Calibration();

  //Main function
  void run_panel();
  void design_panel(k4n::dev::Master* master);

private:
  string name;
  bool* show_window;
};

}
