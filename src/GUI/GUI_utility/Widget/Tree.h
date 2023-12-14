#pragma once

#include "Tree_node.h"
#include "Tree_filler.h"

#include <Utility/Specific/common.h>


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
  void construct_tree(Tree_filler* filler);

  //subfunction
  void construct_node(string path, vector<Tree_node*>& nodes);
  void construct_node_root(vector<string>& vec_path, vector<Tree_node*>& nodes);
  void display_node(Tree_node* node, vector<Tree_node*>& all_nodes);
  void display_node_root(vector<Tree_node*>& all_nodes);
  void node_child_scan(string path, vector<Tree_node*>& nodes, Tree_node* parent);
  bool check_display_file_format(string path);
  void open_selection(Tree_node* node);

private:
  vector<Tree_node*> nodes_root;
  vector<vector<Tree_node*>> nodes_path_vec;
  Tree_filler* filler = nullptr;
};

}
