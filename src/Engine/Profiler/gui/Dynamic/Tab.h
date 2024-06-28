#pragma once

namespace prf{class Node;}
namespace prf{class Structure;}
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
  void draw_tab(int width);

  //Subfunction
  void draw_dynamic_tabbar();

private:
  prf::Structure* prf_struct;
  prf::gui::dynamic::Graph* gui_graph;
};

}
