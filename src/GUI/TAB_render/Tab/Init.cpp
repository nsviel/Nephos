#include "Init.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <Engine/Data/Namespace.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Info.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Init::Init(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();

  this->eng_scene = eng_data->get_eng_scene();
  this->eng_loader = eng_data->get_eng_loader();
  this->transformManager = new eng::ope::Transformation();
  this->gui_tree = new gui::widget::Tree();

  //---------------------------
  this->init_init();
}
Init::~Init(){}

//Main functions
void Init::design_init(){
  //---------------------------

  this->design_option();
  gui_tree->design_tree();

  //---------------------------
}
void Init::design_option(){
  //---------------------------

  //Point cloud scaling
  ImGui::SetNextItemWidth(100);
  ImGui::DragFloat("Scale##4567", &scale, 0.1, 0.1, 100, "%.2f x");
  ImGui::SameLine();

  //Remove old clouds
  ImGui::Checkbox("Remove##222", &remove_old);

  //---------------------------
}

//Subfunction
void Init::init_init(){
  //---------------------------

  //Open accepted formats
  filler.accepted_format.clear();
  filler.accepted_format.push_back("pts");
  filler.accepted_format.push_back("obj");
  filler.accepted_format.push_back("ply");
  filler.accepted_format.push_back("xyz");
  filler.accepted_format.push_back("cbor");
  filler.accepted_format.push_back("pcap");
  filler.accepted_format.push_back("ptx");
  filler.accepted_format.push_back("csv");
  filler.accepted_format.push_back("las");
  filler.accepted_format.push_back("laz");

  //Custom folder tree
  filler.vec_path_folder.clear();
  filler.vec_path_folder.push_back("../media/point_cloud");

  //Custom file leaf
  //filler.vec_path_file.push_back("../media/dragon.ply");

  //Function
  filler.fct_on_click = [this](const std::string path){operation_new_object(path);};

  //---------------------------
  gui_tree->construct_tree(&filler);
}
void Init::load_config_file(){
  //---------------------------


  //---------------------------
}
void Init::operation_new_object(string path){
  if(path == "") return;
  //---------------------------

  eng::structure::Object* object = eng_loader->load_object(path);
  if(object == nullptr) return;

  if(remove_old){
    eng_scene->delete_object_scene_all();
  }

  transformManager->make_scaling(object, scale);

  //---------------------------
}

//Custom scene
void Init::build_custom_scene(vector<vector<Tree_node*>>& nodes_path_vec){
  //---------------------------

  //Scene folder
  /*vector<Tree_node*> root_scene;
  Tree_node* node = new Tree_node();
  node->name = "scene";
  node->type = "Folder";
  node->end_folder = true;
  node->leaf_nb = 3;
  node->leaf_idx = 1;
  node->already_open = true;
  root_scene.push_back(node);

  //Scene 1 -> example of custom scene integration in tree
  /*node = new Tree_node();
  node->name = "Rocks";
  node->leaf_nb = 0;
  node->type = "scene_1";
  root_scene.push_back(node);*/

//  nodes_path_vec.push_back(root_scene);

  //---------------------------
}
void Init::build_scene_1(){
  //---------------------------



  //---------------------------
}

}
