#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <GUI/GUI_utility/Base/Namespace.h>
#include <Engine/Data/Scene/Database.h>

class GUI;

namespace gui::rnd::data{
class Object;
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
  void draw_window_background();
  void tree_view();
  int data_node_tree(eng::data::Set* set);

  bool show_object   = false;
  bool show_set      = false;

private:
  gui::rnd::data::Object* rnd_object;
  gui::rnd::data::Set* rnd_set;
  eng::scene::Database* eng_database;

  bool* panel_show;;
};

}
