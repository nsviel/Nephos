#pragma once

#include <GUI_utility/Base_nsp.h>
#include <UTL_specific/common.h>
#include <TAB_render/Data/Namespace.h>
#include <TAB_render/Tab_nsp.h>

class GUI;
class Set;
class ENG_database;

namespace gui::rnd::panel{
class Object;


class Scene : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Scene(GUI* gui, bool* show_window, string name);
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

  bool* show_window;
};

}
