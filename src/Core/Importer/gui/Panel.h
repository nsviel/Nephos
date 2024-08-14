#pragma once

#include <string>

namespace io::imp{class Node;}
namespace io::imp::gui{class Bookmark;}
namespace io::imp::gui{class Operation;}
namespace io::imp::gui{class Navigator;}


namespace io::imp::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(io::imp::Node* node_importer, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  inline io::imp::Node* get_node_importer(){return node_importer;}
  inline io::imp::gui::Navigator* get_gui_navigator(){return gui_navigator;}

private:
  io::imp::Node* node_importer;
  io::imp::gui::Navigator* gui_navigator;
  io::imp::gui::Bookmark* gui_bookmark;
  io::imp::gui::Operation* gui_operation;

  std::string name;
  bool* show_window;
};

}
