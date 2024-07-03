#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Transformation;}
namespace utl::base{class Element;}
namespace dat::graph{class Selection;}


namespace ldr::gui::transformation{

class Panel
{
public:
  //Constructor / Destructor
  Panel(ldr::Node* node_loader, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel(utl::base::Element* element );

  //Subfunction
  void display_loader(utl::base::Element* element);
  void display_path(utl::base::Element* element);
  void display_format(utl::base::Element* element);
  void display_matrix(utl::base::Element* element);
  void item_filtering(std::vector<std::string>& vec_path);
  void item_operation();

private:
  ldr::Structure* ldr_struct;
  ldr::io::Transformation* ldr_transformation;
  utl::gui::Navigator* gui_navigator;
  dat::graph::Selection* dat_selection;

  std::string name;
  bool* show_window;
};

}
