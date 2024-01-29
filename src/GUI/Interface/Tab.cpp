#include "Tab.h"

#include <Dev/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <GUI/Namespace.h>


namespace gui::interface{

//Constructor / Destructor
Tab::Tab(gui::Node* gui){
  //---------------------------

  this->eng_tab = new eng::gui::Tab(gui->get_engine());
  this->dev_tab = new dev::gui::Tab();
  this->gui_menu = new gui::interface::Menu(gui);

  this->active_tab = "Render";
  this->tab_to_open = "";
  this->vec_tab.push_back("Render");
  this->vec_tab.push_back("Dev");

  //---------------------------
}
Tab::~Tab(){
  //---------------------------

  delete eng_tab;
  delete dev_tab;

  //---------------------------
}

//Main function
void Tab::run_tab(){
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
void Tab::draw_tab(){
  //---------------------------

  //Draw selected tab panels
  if(active_tab == "Render"){
    eng_tab->draw_tab();
  }
  else if(active_tab == "Dev"){
    dev_tab->draw_tab();
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
