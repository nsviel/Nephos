#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace sce{class Node;}
namespace sce{class Database;}
namespace sce{class Set;}
namespace sce::gui{class Entity;}
namespace sce::gui{class Set;}
namespace cam{class Control;}
namespace ope{class Operation;}


namespace sce::gui{

class Graph
{
public:
  //Constructor / Destructor
  Graph(sce::Node* node_scene, bool* show_window);
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
  void tree_entity(utl::type::Set* set, utl::type::Entity* entity, int& nb_row);

  bool show_panel_entity   = false;
  bool show_panel_set      = false;

private:
  eng::Node* node_engine;
  sce::gui::Entity* rnd_object;
  sce::gui::Set* rnd_set;
  sce::Database* sce_database;
  sce::Set* sce_set;
  cam::Control* cam_control;
  ope::Operation* ope_operation;

  string name;
  bool* show_window;
};

}
