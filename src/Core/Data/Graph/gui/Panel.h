#pragma once

#include <string>

namespace dat::gph{class Node;}
namespace dat::gph{class Graph;}
namespace dat::gph::gui{class Set;}


namespace dat::gph::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::gph::Node* node_graph, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void draw_file_tree();
  void draw_window_background(int nb_row);

private:
  dat::gph::Graph* dat_graph;
  dat::gph::gui::Set* gui_set;

  std::string name;
  bool* show_window;
};

}
