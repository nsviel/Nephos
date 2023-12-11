#pragma once

#include <Tab/struct_init.h>
#include <GUI/GUI_utility/Widget/Namespace.h>
#include <Utility/UTL_specific/common.h>

class Init;


namespace gui::widget{

class Tree
{
public:
  //Constructor / Destructor
  Tree();
  ~Tree();

public:
  //Main function
  void design_tree();
  void construct_tree(Struct_init* init);

  //subfunction
  void construct_node(string path, vector<Tree_node*>& nodes);
  void construct_node_root(vector<string>& vec_path, vector<Tree_node*>& nodes);
  void display_node(Tree_node* node, vector<Tree_node*>& all_nodes);
  void display_node_root(vector<Tree_node*>& all_nodes);
  void node_child_scan(string path, vector<Tree_node*>& nodes, Tree_node* parent);
  bool check_display_file_format(string path);
  void open_selection(Tree_node* node);

private:
  Init* gui_init;

  vector<Tree_node*> nodes_root;
  vector<vector<Tree_node*>> nodes_path_vec;
  Struct_init* init;
};

}
