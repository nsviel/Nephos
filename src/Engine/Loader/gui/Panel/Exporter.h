#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::io{class Exporter;}
namespace ldr::gui{class File;}


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

  //Subfunction
  void draw_header();
  void item_operation();

private:
  ldr::io::Exporter* ldr_exporter;

  std::string name = "";
  bool* show_window;
  int selection;
};

}
