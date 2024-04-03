#include "Node.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::gui{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* opt_panel = add_panel("Option##456", ICON_FA_COG, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_operation = node_engine->get_node_operation();

  //Child
  this->gui_option = new eng::gui::Option(this, &opt_panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::gui(){
  //---------------------------

  this->draw_menu();
  gui_option->run_panel();

  //---------------------------
}

//Subfunction
void Node::draw_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    this->menu_panel();
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Loader")){
    this->menu_loader();
  }
  if(ImGui::MenuItem(ICON_FA_CAMERA)){
    this->menu_screenshot();
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}
void Node::menu_panel(){
  vector<utl::gui::Panel*> vec_panel = node_engine->get_vec_panel();
  //---------------------------

  for(int i=0; i<vec_panel.size(); i++){
    utl::gui::Panel* panel = vec_panel[i];
    string title = panel->icon + " " + panel->name;
    ImGui::Checkbox(title.c_str(), &panel->is_open);
  }

  //---------------------------
}
void Node::menu_loader(){
  vector<utl::gui::Panel*> vec_panel = node_engine->get_vec_panel();
  //---------------------------

  for(int i=0; i<vec_panel.size(); i++){
    if(vec_panel[i]->name == "Loader"){
      vec_panel[i]->is_open = !vec_panel[i]->is_open;
    }
  }

  //---------------------------
}
void Node::menu_screenshot(){
  vk::image::Screenshot* vk_screenshot = node_vulkan->get_vk_screenshot();
  //---------------------------

  vk_screenshot->make_screenshot();

  //---------------------------
}


}
