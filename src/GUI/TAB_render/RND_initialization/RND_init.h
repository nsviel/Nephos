#pragma once

#include "struct_node.h"
#include "struct_init.h"
#include <UTL_specific/common.h>

class GUI;
class ENG_scene;
class ENG_loader;
class Transformation;
class RND_tree;


class RND_init
{
public:
  //Constructor / Destructor
  RND_init(GUI* gui);
  ~RND_init();

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
  ENG_scene* eng_scene;
  ENG_loader* eng_loader;
  Transformation* transformManager;
  RND_tree* gui_tree;

  vector<Tree_node*> nodes_root;
  vector<vector<Tree_node*>> nodes_path_vec;

  Struct_init init;
};
