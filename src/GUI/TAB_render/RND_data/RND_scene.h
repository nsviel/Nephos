#pragma once

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class RND_panel;
class RND_object;
class RND_set;
class ENG_database;


class RND_scene : public BASE_panel
{
public:
  //Constructor / Destructor
  RND_scene(GUI* gui, bool* show_window, string name);
  ~RND_scene();

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
  RND_object* gui_object;
  RND_set* gui_set;
  ENG_database* eng_database;

  bool* show_window;
};
