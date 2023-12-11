#pragma once

#include "struct_init.h"
#include <Engine/Data/Namespace.h>
#include <GUI/GUI_utility/Widget/Tree_node.h>
#include <Utility/UTL_specific/common.h>
#include <GUI/GUI_utility/Widget/Namespace.h>

class GUI;

class Transformation;


namespace gui::rnd::tab{

class Init
{
public:
  //Constructor / Destructor
  Init(GUI* gui);
  ~Init();

public:
  //Main funxtion
  void design_init();
  void design_option();

  //Subfunction
  void init_init();
  void load_config_file();
  void operation_new_object(string path);

  //Custom scene
  void build_custom_scene(vector<vector<Tree_node*>>& nodes_path_vec);
  void build_scene_1();

private:
  eng::data::Scene* eng_scene;
  eng::data::ENG_loader* eng_loader;
  Transformation* transformManager;
  gui::widget::Tree* gui_tree;

  vector<Tree_node*> nodes_root;
  vector<vector<Tree_node*>> nodes_path_vec;

  Struct_init init;
};

}
