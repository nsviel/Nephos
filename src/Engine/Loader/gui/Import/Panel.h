#pragma once

#include <string>

namespace ldr{class Node;}
namespace ldr::gui::importer{class Bookmark;}
namespace ldr::gui::importer{class Operation;}
namespace ldr::gui::importer{class Navigator;}


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

  inline ldr::Node* get_node_loader(){return node_loader;}

private:
  ldr::Node* node_loader;
  ldr::gui::importer::Navigator* gui_navigator;
  ldr::gui::importer::Bookmark* gui_bookmark;
  ldr::gui::importer::Operation* gui_operation;

  std::string name;
  bool* show_window;
};

}
