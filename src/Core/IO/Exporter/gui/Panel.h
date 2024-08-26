#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <memory>
#include <string>
#include <vector>

namespace io::exp{class Node;}
namespace io::exp{class Structure;}
namespace io::exp{class Exporter;}
namespace io::exp::gui{class Exporter;}
namespace io::exp::gui{class Recorder;}
namespace utl::gui::navigator{class Item;}
namespace utl::base{class Element;}
namespace dat::gph{class Selection;}


namespace io::exp::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(io::exp::Node* node_exporter, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel(std::shared_ptr<utl::base::Element> element);

  //Navigator
  void item_filtering(std::vector<std::string>& vec_path);
  void item_operation();

private:
  io::exp::Structure* io_struct;
  io::exp::Exporter* io_exporter;
  dat::gph::Selection* gph_selection;
  utl::gui::Navigator* gui_navigator;
  io::exp::gui::Exporter* gui_exporter;
  io::exp::gui::Recorder* gui_recorder;

  std::string name = "";
  bool* show_window;
  int selection;
};

}
