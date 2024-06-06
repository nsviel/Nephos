#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Exporter;}
namespace ldr::gui{class File;}
namespace dat{class Selection;}


namespace ldr::gui{

class Exporter : public ldr::gui::Navigator
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader, bool* show_window);
  ~Exporter();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Header
  void display_action(std::string name);
  void display_path();
  void display_format();
  void display_encording();

  //Navigator
  void item_update();
  void item_operation();
  bool item_format(std::string format);

private:
  ldr::Structure* ldr_struct;
  ldr::io::Exporter* ldr_exporter;
  dat::Selection* dat_selection;

  std::string name = "";
  bool* show_window;
  int selection;
};

}
