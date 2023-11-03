#ifndef GUI_SCENE_H
#define GUI_SCENE_H

#include <RES_base/BASE_panel.h>
#include <ELE_specific/common.h>

class GUI;
class RND_panel;
class PAN_object;
class PAN_set;
class Database;


class PAN_scene : public BASE_panel
{
public:
  //Constructor / Destructor
  PAN_scene(GUI* gui, bool* show_window, string name);
  ~PAN_scene();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void draw_window_background();
  void tree_view();
  int data_node_tree(Set* set);

private:
  RND_panel* gui_render_panel;
  PAN_object* gui_object;
  PAN_set* gui_set;
  Database* dataManager;

  bool* show_window;
};

#endif
