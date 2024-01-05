#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Data/Namespace.h>
#include <GUI/TAB_render/Tab/Namespace.h>

class GUI;

namespace gui::rnd::data{
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
  int data_node_tree(eng::structure::Set* set);

private:
  gui::rnd::tab::Panel* tab_panel;
  gui::rnd::data::Object* panel_object;
  gui::rnd::data::Set* panel_set;
  eng::data::Database* eng_database;

  bool* panel_show;;
};

}
