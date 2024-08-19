#pragma once

#include <string>

namespace prf{class Node;}
namespace prf::gui::dynamic{class Tab;}
namespace prf::gui::hardware{class Tab;}


namespace prf::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(prf::Node* node_profiler, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction

private:
  prf::gui::dynamic::Tab* tab_dynamic;
  prf::gui::hardware::Tab* tab_hardware;

  std::string gpu = "";
  std::string name;
  bool* show_window;
  int width;
};

}
