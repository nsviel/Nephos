#include "Tab.h"

#include <GUI/Namespace.h>
#include <Core/Namespace.h>
#include <Scene/Namespace.h>
#include <Utility/Namespace.h>


namespace gui{

//Constructor / Destructor
Tab::Tab(gui::Node* node_gui){
  //---------------------------

  this->node_scene = node_gui->get_node_scene();
  this->node_core = node_gui->get_node_core();

  this->gui_menu = new gui::interface::Menu(node_gui);
  this->dev_menu = new gui::tab::dev::Menu();
  this->eng_menu = new gui::tab::eng::Menu(node_gui);

  this->active_tab = "Engine";
  this->tab_to_open = "";
  this->vec_tab.push_back("Engine");
  this->vec_tab.push_back("Dev");

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::loop(){
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
void Tab::draw_tab_menu(){
  ImGuiTabItemFlags flag;
  //---------------------------

  if(ImGui::BeginTabBar("main_tab")){
    for(int i=0; i<vec_tab.size(); i++){
      if(tab_to_open == vec_tab[i]){
        flag = ImGuiTabItemFlags_SetSelected;
        this->tab_to_open = "";
      }else{
        flag = 0;
      }
      ImGui::SetNextItemWidth(100);
      if(ImGui::BeginTabItem(vec_tab[i].c_str(), NULL, flag)){
        this->active_tab = vec_tab[i];
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Tab::draw_tab(){
  //---------------------------

  //Draw selected tab panels
  if(active_tab == "Engine"){
    node_scene->gui();
    node_core->gui();
    eng_menu->draw();
  }
  else if(active_tab == "Dev"){
    dev_menu->draw();
  }

  //---------------------------
}
void Tab::next_tab(){
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
