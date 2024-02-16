#include "Node.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::gui{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* opt_panel = new_panel("Option##456", ICON_FA_COG, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;

  //Child
  this->gui_option = new eng::gui::Option(node_engine, &opt_panel->is_open);

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
    vector<utl::gui::Panel*> vec_panel = node_engine->get_vec_panel();
    for(int i=0; i<vec_panel.size(); i++){
      utl::gui::Panel* panel = vec_panel[i];
      string title = panel->icon + " " + panel->name;
      ImGui::Checkbox(title.c_str(), &panel->is_open);
    }
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Loader")){
    vector<utl::gui::Panel*> vec_panel = node_engine->get_vec_panel();
    for(int i=0; i<vec_panel.size(); i++){
      if(vec_panel[i]->name == "Loader"){
        vec_panel[i]->is_open = !vec_panel[i]->is_open;
      }
    }
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}


}
