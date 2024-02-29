#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene::gui{class Entity;}
namespace eng::scene::gui{class Set;}
namespace eng::cam{class Control;}
namespace ope{class Operation;}


namespace eng::scene::gui{

class Scene
{
public:
  //Constructor / Destructor
  Scene(eng::scene::Node* node_scene, bool* show_window);
  ~Scene();

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
  eng::scene::gui::Entity* rnd_object;
  eng::scene::gui::Set* rnd_set;
  eng::scene::Database* sce_database;
  eng::cam::Control* cam_control;
  ope::Operation* ope_operation;

  string name;
  bool* show_window;
};

}
