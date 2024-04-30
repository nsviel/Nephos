#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace dat{class Node;}
namespace dat{class Database;}
namespace dat{class Set;}
namespace dat::gui{class Entity;}
namespace dat::gui{class Set;}
namespace cam{class Control;}
namespace ope{class Operation;}
namespace utl::type{class Set;}
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
  void draw_button();
  void draw_window_background();
  void draw_file_tree();

  //File tree
  int tree_set(utl::type::Set* set);
  void tree_set_double_click(utl::type::Set* set);
  void tree_set_open(utl::type::Set* set, int& nb_row);
  void tree_entity(utl::type::Set* set, dat::base::Entity* entity, int& nb_row);

  bool show_panel_entity   = false;
  bool show_panel_set      = false;

private:
  eng::Node* node_engine;
  dat::gui::Entity* rnd_object;
  dat::gui::Set* rnd_set;
  dat::Database* dat_database;
  dat::Set* dat_set;
  cam::Control* cam_control;
  ope::Operation* ope_operation;

  string name;
  bool* show_window;
};

}
