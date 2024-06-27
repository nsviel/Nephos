#pragma once

namespace prf{class Node;}
namespace prf::gui::dynamic{class Graph;}


namespace prf::gui::dynamic{

class Tab
{
public:
  //Constructor / Destructor
  Tab(prf::Node* node_profiler);
  ~Tab();

public:
  //Main function
  void draw_tab();

  //Subfunction
  void draw_dynamic_tabbar();

private:
  prf::gui::dynamic::Graph* gui_graph;
};

}
