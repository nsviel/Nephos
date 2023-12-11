#include "Tree.h"

#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Info.h>


namespace gui::widget{

//Constructor / Destructor
Tree::Tree(){}
Tree::~Tree(){}

//Tree view
void Tree::design_tree(){
  //---------------------------

  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_Resizable;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;
  if (ImGui::BeginTable("init_tree", 3, flags)){
    // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide, 175);
    ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75);
    ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 75);
    ImGui::TableHeadersRow();

    //Display pre-built trees
    this->display_node_root(nodes_root);
    for(int i=0; i<nodes_path_vec.size(); i++){
      this->display_node(nodes_path_vec[i][0], nodes_path_vec[i]);
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Tree::construct_tree(Struct_init* init){
  this->nodes_path_vec.clear();
  this->init = init;
  //---------------------------

  //Construct init path nodes for specific cloud locations
  this->construct_node_root(init->vec_path_file, nodes_root);

  //Set a node for specific scene construction
  //this->build_custom_scene(nodes_path_vec);

  //Construct predefined init path nodes
  for(int i=0; i<init->vec_path_folder.size(); i++){
    vector<Tree_node*> nodes_path;
    this->construct_node(init->vec_path_folder[i], nodes_path);
    this->nodes_path_vec.push_back(nodes_path);
  }

  //---------------------------
}

//subfunction
void Tree::construct_node(string path, vector<Tree_node*>& nodes){
  if(path != ""){
    //---------------------------

    //Save root
    Tree_node* node = new Tree_node();
    node->name = info::get_filename_from_path(path);
    node->type = info::get_type_from_path(path);
    node->path = path;
    node->size = info::get_file_size(path);
    nodes.push_back(node);

    //Recussively check all child leafs
    this->node_child_scan(path, nodes, node);

    //---------------------------
  }
}
void Tree::construct_node_root(vector<string>& vec_path, vector<Tree_node*>& nodes){
  //---------------------------

  for(int i=0; i<vec_path.size(); i++){
    if(vec_path[i] != ""){
      Tree_node* node = new Tree_node();

      node->name = info::get_filename_from_path(vec_path[i]);
      node->type = info::get_type_from_path(vec_path[i]);
      node->path = vec_path[i];
      node->size = info::get_file_size(vec_path[i]);
      node->leaf_nb = 1;
      node->leaf_idx = 1;
      node->already_open = true;
      node->end_folder = true;

      nodes.push_back(node);
    }
  }

  //---------------------------
}
void Tree::node_child_scan(string path, vector<Tree_node*>& nodes, Tree_node* parent){
  vector<string> list_path = directory::list_all_path(path);
  //---------------------------

  bool is_sub_folder = false;
  int id = nodes.size();
  parent->leaf_nb = list_path.size();
  parent->leaf_idx = id;
  parent->already_open = true;

  for(int i=0; i<list_path.size(); i++){
    string path_file = list_path[i];

    Tree_node* node = new Tree_node();
    node->name = info::get_filename_from_path(path_file);
    node->type = info::get_type_from_path(path_file);
    node->path = path_file;

    if(node->type != "Folder"){
      if(check_display_file_format(path_file)){
        node->leaf_nb = 0;
        node->size = info::get_file_size(path_file);
        nodes.push_back(node);
      }else{
        parent->leaf_nb--;
        delete node;
      }
    }else{
      is_sub_folder = true;
      node->leaf_nb = 1;
      nodes.push_back(node);
    }
  }

  if(is_sub_folder){
    parent->end_folder = false;
  }else{
    parent->end_folder = true;
  }

  //---------------------------
}
void Tree::display_node(Tree_node* node, vector<Tree_node*>& all_nodes){
  if(all_nodes.size() != 0){
    //---------------------------

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    const bool is_folder = (node->leaf_nb > 0);
    if(is_folder){
      ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;
      bool open = ImGui::TreeNodeEx(node->name.c_str(), node_flags);
      if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
        if(node->already_open == false){
          this->node_child_scan(node->path, all_nodes, node);
        }
        this->open_selection(node);
      }
      ImGui::TableNextColumn();
      ImGui::TextDisabled("--");
      ImGui::TableNextColumn();
      ImGui::TextUnformatted(node->type.c_str());
      if(open){
        if(node->already_open == false){
          this->node_child_scan(node->path, all_nodes, node);
        }
        for(int i=0; i<node->leaf_nb; i++){
          int id = node->leaf_idx + i;
          display_node(all_nodes[id], all_nodes);
        }
        ImGui::TreePop();
      }
    }
    else if(node->type != "Folder"){
      ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth;
      ImGui::TreeNodeEx(node->name.c_str(), node_flags);
      if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
        this->open_selection(node);
      }
      ImGui::TableNextColumn();
      ImGui::Text("%.1f MB", node->size);
      ImGui::TableNextColumn();
      ImGui::TextUnformatted(node->type.c_str());
    }

    //---------------------------
  }
}
void Tree::display_node_root(vector<Tree_node*>& all_nodes){
  //---------------------------

  for(int i=0; i<all_nodes.size(); i++){
    Tree_node* node = all_nodes[i];

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth;
    ImGui::TreeNodeEx(node->name.c_str(), node_flags);
    if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
      this->open_selection(node);
    }
    ImGui::TableNextColumn();
    ImGui::Text("%.1f MB", node->size);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(node->type.c_str());
  }

  //---------------------------
}
bool Tree::check_display_file_format(string path){
  string format = info::get_format_from_path(path);
  //---------------------------

  for(int i=0; i<init->accepted_format.size(); i++){
    if(format == init->accepted_format[i]){
      return true;
    }
  }

  //---------------------------
  return false;
}
void Tree::open_selection(Tree_node* node){
  //---------------------------

  if(node->type == "File"){
    //gui_init->operation_new_object(node->path);
  }
  /*else if(node->type == "Folder" && node->end_folder){
    if(pathManager->check_folder_format(node->path, "ply")){
      eng::structure::Object* object;

      if(with_onthefly == false){
        object = pathManager->loading_directory_frame(node->path);
      }else{
        object = pathManager->loading_onthefly(node->path);
      }

      this->operation_new_collection(object);
    }
  }*/
  else if(node->type == "scene_1"){
    //this->build_scene_1();
  }

  //---------------------------
}

}
