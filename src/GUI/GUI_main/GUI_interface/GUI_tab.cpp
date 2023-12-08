#include "GUI_tab.h"

#include <GUI.h>
#include <Vulkan.h>
#include <GUI_interface/GUI_menu.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
GUI_tab::GUI_tab(GUI* gui){
  //---------------------------

  this->rnd_tab = new gui::rnd::tab::Tab(gui);
  this->dev_tab = new gui::dev::tab::Tab(gui);
  this->gui_menu = new GUI_menu(gui);

  this->active_tab = "Render";
  this->tab_to_open = "";
  this->vec_tab.push_back("Render");
  this->vec_tab.push_back("Dev");

  //---------------------------
}
GUI_tab::~GUI_tab(){
  //---------------------------

  delete rnd_tab;
  delete dev_tab;

  //---------------------------
}

//Main function
void GUI_tab::create_panels(){
  //---------------------------

  rnd_tab->create_panels();
  dev_tab->create_panels();

  //---------------------------
}
void GUI_tab::run_tab(){
  //---------------------------

  //Draw main menu bar
  ImGui::BeginMainMenuBar();
  gui_menu->menu();
  ImGui::Separator();
  this->tabs();
  ImGui::Dummy(ImVec2(100.0f, 0.0f)); // empty space
  ImGui::EndMainMenuBar();
  this->draw_panels();

  //---------------------------
}

//Tab function
void GUI_tab::tabs(){
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
void GUI_tab::draw_panels(){
  //---------------------------

  //Draw selected tab panels
  if(active_tab == "Render"){
    rnd_tab->draw_panels();
  }
  else if(active_tab == "Dev"){
    dev_tab->draw_panels();
  }

  //---------------------------
}
void GUI_tab::next_tab(){
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
