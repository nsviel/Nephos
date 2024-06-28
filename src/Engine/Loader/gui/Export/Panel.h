#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Exporter;}
namespace ldr::gui{class File;}
namespace ldr::gui::exporter{class Exporter;}
namespace ldr::gui::exporter{class Recorder;}
namespace dat::graph{class Selection;}
namespace utl::base{class Element;}


namespace ldr::gui::exporter{

class Panel : public ldr::gui::Navigator
{
public:
  //Constructor / Destructor
  Panel(ldr::Node* node_loader, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel(utl::base::Element* element);

  //Navigator
  void item_filtering(std::vector<std::string>& vec_path);
  void item_operation();

private:
  ldr::Structure* ldr_struct;
  ldr::io::Exporter* ldr_exporter;
  dat::graph::Selection* dat_selection;
  ldr::gui::exporter::Exporter* gui_exporter;
  ldr::gui::exporter::Recorder* gui_recorder;

  std::string name = "";
  bool* show_window;
  int selection;
};

}
