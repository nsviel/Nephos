#pragma once

#include <string>

namespace dat::elm{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace dat::gui::entity{class Panel;}
namespace dat::gui::set{class Panel;}
namespace dat::gph{class Node;}
namespace dat::gph{class Selection;}
namespace dat::gph{class Graph;}
namespace dat::gph::gui{class Button;}


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
  int tree_set(dat::base::Set* set);
  void tree_set_open(dat::base::Set* set, int& nb_row);
  void tree_entity(dat::base::Set* set, dat::base::Entity* entity, int& nb_row);
  void draw_window_background(int nb_row);

  bool show_panel_entity   = false;
  bool show_panel_set      = false;

private:
  dat::gph::Graph* dat_graph;
  dat::gph::Selection* dat_selection;
  dat::elm::Set* dat_set;
  dat::gui::entity::Panel* gui_entity;
  dat::gui::set::Panel* gui_set;
  dat::gph::gui::Button* gui_button;

  std::string name;
  bool* show_window;
};

}
