#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <GUI/GUI_utility/Base/Namespace.h>
#include <Engine/Scene/Data/Database.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Base/Namespace.h>

class GUI;

namespace gui::rnd::data{
class Entity;
class Set;


class Scene : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Scene(GUI* gui, bool* show_window, string name);
  ~Scene();

public:
  //Main function
  void design_panel();

  //Subfunction
  void draw_button();
  void draw_window_background();
  void draw_tree_view();
  int data_node_tree(eng::base::Set* set);

  bool show_object   = false;
  bool show_set      = false;

private:
  gui::rnd::data::Entity* rnd_object;
  gui::rnd::data::Set* rnd_set;
  eng::scene::Scene* sce_scene;
  eng::scene::Operation* sce_operation;
  eng::scene::Database* sce_database;
  eng::camera::Control* cam_control;

  bool* panel_show;;
};

}
