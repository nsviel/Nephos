#pragma once

#include <string>

namespace dat{class Node;}
namespace dat{class Graph;}
namespace dat::element{class Set;}
namespace dat::graph{class Selection;}
namespace dat{class Structure;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace dat::gui::entity{class Panel;}
namespace dat::gui::set{class Panel;}
namespace dat::gui::graph{class Button;}


namespace dat::gui::graph{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::Node* node_data, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void draw_file_tree();
  int tree_set(dat::base::Set* set);
  void tree_set_open(dat::base::Set* set, int& nb_row);
  void tree_entity(dat::base::Set* set, dat::base::Entity* entity, int& nb_row);
  void draw_window_background(int nb_row);

  bool show_panel_entity   = false;
  bool show_panel_set      = false;

private:
  dat::Structure* dat_struct;
  dat::Graph* dat_graph;
  dat::graph::Selection* dat_selection;
  dat::element::Set* dat_set;
  dat::gui::entity::Panel* gui_entity;
  dat::gui::set::Panel* gui_set;
  dat::gui::graph::Button* gui_button;

  std::string name;
  bool* show_window;
};

}
