#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <Panel/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class Panel;
class GUI_object;
class GUI_set;
class Database;


class GUI_scene : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_scene(GUI* gui, bool* show_window, string name);
  ~GUI_scene();

public:
  //Main function
  void design_panel();

  //Subfunction
  void draw_window_background();
  void tree_view();
  int data_node_tree(Set* set);

private:
  Panel* panel;
  GUI_object* gui_object;
  GUI_set* gui_set;
  Database* dataManager;
};

#endif
