#pragma once

#include <UTL_specific/common.h>
#include <GUI/TAB_render/Data/Namespace.h>
#include <GUI/TAB_render/Tab/Namespace.h>

class GUI;

namespace gui::rnd::panel{
class Object;
class Set;


class Scene
{
public:
  //Constructor / Destructor
  Scene(GUI* gui, gui::rnd::tab::Panel* tab_panel);
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
  gui::rnd::tab::Panel* tab_panel;
  gui::rnd::panel::Object* panel_object;
  gui::rnd::panel::Set* panel_set;

  list<data::Set*>* list_data;
  string panel_name;
  bool* panel_show;;
};

}
