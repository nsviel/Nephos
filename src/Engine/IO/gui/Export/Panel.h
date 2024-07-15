#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace io{class Node;}
namespace io{class Structure;}
namespace io{class Exporter;}
namespace utl::gui::navigator{class Item;}
namespace io::gui::exporter{class Exporter;}
namespace io::gui::exporter{class Recorder;}
namespace dat::graph{class Selection;}
namespace utl::base{class Element;}


namespace io::gui::exporter{

class Panel
{
public:
  //Constructor / Destructor
  Panel(io::Node* node_io, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel(utl::base::Element* element);

  //Navigator
  void item_filtering(std::vector<std::string>& vec_path);
  void item_operation();

private:
  io::Structure* io_struct;
  io::Exporter* io_exporter;
  dat::graph::Selection* dat_selection;
  utl::gui::Navigator* gui_navigator;
  io::gui::exporter::Exporter* gui_exporter;
  io::gui::exporter::Recorder* gui_recorder;

  std::string name = "";
  bool* show_window;
  int selection;
};

}
