#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}


namespace ldr::gui::transformation{

class Panel : public ldr::gui::Navigator
{
public:
  //Constructor / Destructor
  Panel(ldr::Node* node_loader, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void draw_header();

private:
  ldr::Structure* ldr_struct;

  std::string name;
  bool* show_window;
};

}
