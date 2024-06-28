#pragma once

#include <string>

namespace dat{class Node;}
namespace dat{class Graph;}
namespace dat::element{class Set;}
namespace dat::graph{class Selection;}
namespace dat{class Structure;}
namespace dat::gui{class Entity;}
namespace dat::gui{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dat::gui{

class Graph
{
public:
  //Constructor / Destructor
  Graph(dat::Node* node_data, bool* show_window);
  ~Graph();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void draw_window_background();
  void draw_file_tree();

  //File tree
  int tree_set(dat::base::Set* set);
  void tree_set_open(dat::base::Set* set, int& nb_row);
  void tree_entity(dat::base::Set* set, dat::base::Entity* entity, int& nb_row);

  bool show_panel_entity   = false;
  bool show_panel_set      = false;

private:
  dat::gui::Entity* rnd_object;
  dat::gui::Set* rnd_set;
  dat::Graph* dat_graph;
  dat::graph::Selection* dat_selection;
  dat::element::Set* dat_set;
  dat::Structure* dat_struct;

  std::string name;
  bool* show_window;
};

}
