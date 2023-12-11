#include "Init.h"

#include <Node/GUI.h>
#include <Engine/Node/Engine.h>
#include <Engine/ENG_data/ENG_data.h>
#include <Engine/ENG_data/ENG_scene/ENG_scene.h>
#include <Engine/ENG_data/ENG_load/ENG_loader.h>
#include <Engine/ENG_operation/Transformation/Transformation.h>
#include <Utility/UTL_file/Directory.h>
#include <Utility/UTL_file/Info.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Init::Init(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  ENG_data* eng_data = engine->get_eng_data();

  this->eng_scene = eng_data->get_eng_scene();
  this->eng_loader = eng_data->get_eng_loader();
  this->transformManager = new Transformation();
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
  ImGui::DragFloat("Scale##4567", &init.scale, 0.1, 0.1, 100, "%.2f x");
  ImGui::SameLine();

  //Remove old clouds
  ImGui::Checkbox("Remove##222", &init.remove_old);

  //---------------------------
}

//Subfunction
void Init::init_init(){
  //---------------------------

  this->init.remove_old = true;
  this->init.scale = 1;

  //Open accepted formats
  this->init.accepted_format.push_back("pts");
  this->init.accepted_format.push_back("obj");
  this->init.accepted_format.push_back("ply");
  this->init.accepted_format.push_back("xyz");
  this->init.accepted_format.push_back("cbor");
  this->init.accepted_format.push_back("pcap");
  this->init.accepted_format.push_back("ptx");
  this->init.accepted_format.push_back("csv");
  this->init.accepted_format.push_back("las");
  this->init.accepted_format.push_back("laz");

  //Custom folder tree
  this->init.vec_path_folder.push_back("../media/point_cloud");

  //Custom file leaf
  //this->init.vec_path_file.push_back("../media/dragon.ply");

  //---------------------------
  gui_tree->construct_tree(&init);
}
void Init::load_config_file(){
  //---------------------------



  //---------------------------
}
void Init::operation_new_object(string path){
  //---------------------------

  eng::structure::Object* object = eng_loader->load_object(path);
  if(object == nullptr) return;

  if(init.remove_old){
    eng_scene->empty_scene_set();
  }

  transformManager->make_scaling(object, init.scale);

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
