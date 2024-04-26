#include "Node.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <GUI/Namespace.h>


namespace gui::tab{

//Constructor / Destructor
Node::Node(gui::Node* gui){
  //---------------------------

  this->node_engine = gui->get_node_engine();
  this->tab_dev = new dev::gui::Node();
  this->gui_menu = new gui::interface::Menu(gui);
  this->tab_engine = new eng::gui::Node(node_engine);

  this->active_tab = "Engine";
  this->tab_to_open = "";
  this->vec_tab.push_back("Engine");
  this->vec_tab.push_back("Dev");
  this->add_node_panel(tab_engine);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::loop(){
  //---------------------------

  this->run_tab();
  tab_engine->gui();

  //---------------------------
}

//Subfunction
void Node::run_tab(){
  //---------------------------

  //Draw main menu bar
  ImGui::BeginMainMenuBar();
  gui_menu->menu();
  ImGui::Separator();
  this->draw_tab_menu();
  ImGui::Dummy(ImVec2(100.0f, 0.0f)); // empty space
  ImGui::EndMainMenuBar();
  this->draw_tab();

  //---------------------------
}

//Tab function
void Node::draw_tab_menu(){
  ImGuiTabItemFlags flag;
  //---------------------------

  if (ImGui::BeginTabBar("main_tab")){
    for(int i=0; i<vec_tab.size(); i++){
      if(tab_to_open == vec_tab[i]){
        flag = ImGuiTabItemFlags_SetSelected;
        this->tab_to_open = "";
      }else{
        flag = 0;
      }
      ImGui::SetNextItemWidth(100);
      if (ImGui::BeginTabItem(vec_tab[i].c_str(), NULL, flag)){
        this->active_tab = vec_tab[i];
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Node::draw_tab(){
  //---------------------------

  //Draw selected tab panels
  if(active_tab == "Engine"){
    node_engine->gui();
  }
  else if(active_tab == "Dev"){
    tab_dev->draw_tab();
  }

  //---------------------------
}
void Node::next_tab(){
  //---------------------------

  for(int i=0; i<vec_tab.size(); i++){
    if(vec_tab[i] == active_tab){
      if(i == vec_tab.size()-1){
        this->tab_to_open = vec_tab[0];
      }else{
        this->tab_to_open = vec_tab[i+1];
      }
    }
  }

  //---------------------------
}

}
