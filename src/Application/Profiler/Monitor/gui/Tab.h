#pragma once

namespace prf::monitor{class Node;}
namespace prf::monitor{class Structure;}
namespace prf::gui::dynamic{class Graph;}


namespace prf::gui::dynamic{

class Tab
{
public:
  //Constructor / Destructor
  Tab(prf::monitor::Node* node_monitor);
  ~Tab();

public:
  //Main function
  void draw_tab(int width);

  //Subfunction
  void draw_dynamic_tabbar();

private:
  prf::monitor::Structure* prf_struct;
  prf::gui::dynamic::Graph* gui_graph;
};

}
