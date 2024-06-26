#pragma once

#include <Utility/GUI/Tree/Node.h>
#include <Utility/GUI/Tree/Filler.h>
#include <Utility/Specific/Common.h>


namespace utl::gui{

class Tree
{
public:
  //Constructor / Destructor
  Tree();
  ~Tree();

public:
  //Main function
  void design_tree();
  void construct_tree(utl::gui::tree::Filler* filler);

  //subfunction
  void construct_node(std::string path, vector<utl::gui::tree::Node*>& nodes);
  void construct_node_root(std::vector<string>& vec_path, vector<utl::gui::tree::Node*>& nodes);
  void display_node(utl::gui::tree::Node* node, vector<utl::gui::tree::Node*>& all_nodes);
  void display_node_root(std::vector<utl::gui::tree::Node*>& all_nodes);
  void node_child_scan(std::string path, vector<utl::gui::tree::Node*>& nodes, utl::gui::tree::Node* parent);
  bool check_display_file_format(std::string path);
  void open_selection(utl::gui::tree::Node* node);

private:
  vector<utl::gui::tree::Node*> nodes_root;
  vector<vector<utl::gui::tree::Node*>> nodes_path_vec;
  utl::gui::tree::Filler* filler = nullptr;
};

}
