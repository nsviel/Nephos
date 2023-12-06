#include "GUI_tab.h"

#include <GUI.h>
#include <Vulkan.h>
#include <GUI_interface/GUI_menu.h>
#include <image/IconsFontAwesome5.h>
#include <TAB_render/RND_tab.h>
#include <TAB_dev/TAB_dev.h>


//Constructor / Destructor
GUI_tab::GUI_tab(GUI* gui){
  //---------------------------

  this->gui_tab_render = new RND_tab(gui);
  this->gui_tab_dev = new TAB_dev(gui);
  this->gui_menu = new GUI_menu(gui);

  this->active_tab = "Render";
  this->tab_to_open = "";
  this->vec_tab.push_back("Render");
  this->vec_tab.push_back("Dev");

  //---------------------------
}
GUI_tab::~GUI_tab(){
  //---------------------------

  delete gui_tab_render;
  delete gui_tab_dev;

  //---------------------------
}

//Main function
void GUI_tab::create_panels(){
  //---------------------------

  gui_tab_render->create_panels();
  gui_tab_dev->create_panels();

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
    gui_tab_render->draw_panels();
  }
  else if(active_tab == "Dev"){
    gui_tab_dev->draw_panels();
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
