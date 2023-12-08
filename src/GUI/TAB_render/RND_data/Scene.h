#pragma once

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>
#include <TAB_render/Panel_nsp.h>

class GUI;
class RND_panel;
class Set;
class ENG_database;

namespace gui::rnd::panel{
class Object;


class Scene : public BASE_panel
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
  RND_panel* rnd_panel;
  gui::rnd::panel::Object* gui_object;
  Set* gui_set;
  ENG_database* eng_database;

  bool* show_window;
};

}
