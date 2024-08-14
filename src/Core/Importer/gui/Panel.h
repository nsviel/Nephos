#pragma once

#include <string>

namespace io{class Node;}
namespace io::imp::gui{class Bookmark;}
namespace io::imp::gui{class Operation;}
namespace io::imp::gui{class Navigator;}


namespace io::imp::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(io::Node* node_io, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  inline io::Node* get_node_io(){return node_io;}
  inline io::gui::importer::Navigator* get_gui_navigator(){return gui_navigator;}

private:
  io::Node* node_io;
  io::gui::importer::Navigator* gui_navigator;
  io::gui::importer::Bookmark* gui_bookmark;
  io::gui::importer::Operation* gui_operation;

  std::string name;
  bool* show_window;
};

}
