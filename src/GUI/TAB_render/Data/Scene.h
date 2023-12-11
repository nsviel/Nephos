#pragma once

#include <UTL_specific/common.h>
#include <TAB_render/Data/Namespace.h>

class GUI;

namespace gui::rnd::panel{
class Object;
class Set;


class Scene
{
public:
  //Constructor / Destructor
  Scene(GUI* gui, gui::rnd::tab::Panel* rnd_panel);
  ~Scene();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void draw_window_background();
  void tree_view();
  int data_node_tree(data::Set* set);

private:
  gui::rnd::tab::Panel* rnd_panel;
  gui::rnd::panel::Object* gui_object;
  Set* gui_set;
  ENG_database* eng_database;

  string panel_name;
  bool* panel_show;;
};

}
