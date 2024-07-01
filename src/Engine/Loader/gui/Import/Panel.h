#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::gui::navigator{class File;}
namespace ldr::bookmark{class Manager;}
namespace dat{class Graph;}
namespace dat::element{class Set;}
namespace dat::base{class Entity;}


namespace ldr::gui::importer{

class Panel
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
  void draw_body();
  void draw_bookmark_tab();

  //Operation function
  void item_operation();
  void item_bookmark(std::string path);

private:
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;
  dat::element::Set* dat_set;
  dat::Graph* dat_graph;
  ldr::gui::Navigator* gui_navigator;
  
  std::string name;
  bool goto_file_tab = false;
  bool* show_window;
};

}
