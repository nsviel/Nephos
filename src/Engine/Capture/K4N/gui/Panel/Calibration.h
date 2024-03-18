#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}


namespace k4n::gui{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(k4n::Node* node_k4n, bool* show_window);
  ~Calibration();

  //Main function
  void run_panel();
  void design_panel();

private:
  string name;
  bool* show_window;
};

}
