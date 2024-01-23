#pragma once


#include <Utility/Specific/common.h>
#include <Utility/Base/GUI/Panel.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Data/gui/Entity.h>
#include <Engine/Data/gui/Set.h>

class Engine;

namespace gui::rnd::data{
class Entity;
class Set;


class Scene : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Scene(Engine* engine, bool* show_window, string name);
  ~Scene();

public:
  //Main function
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
  gui::rnd::data::Entity* rnd_object;
  gui::rnd::data::Set* rnd_set;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  camera::src::Control* cam_control;
  ope::src::Operation* ope_operation;

  bool* panel_show;;
};

}
