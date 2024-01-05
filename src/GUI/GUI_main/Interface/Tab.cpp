#include "Tab.h"

#include <Node/GUI.h>
#include <Vulkan/Vulkan.h>


namespace gui{

//Constructor / Destructor
Tab::Tab(GUI* gui){
  //---------------------------

  this->rnd_panel = new gui::rnd::tab::Panel(gui);
  this->dev_panel = new gui::dev::tab::Panel(gui);
  this->gui_menu = new gui::Menu(gui);

  this->active_tab = "Render";
  this->tab_to_open = "";
  this->vec_tab.push_back("Render");
  this->vec_tab.push_back("Dev");

  //---------------------------
}
Tab::~Tab(){
  //---------------------------

  delete rnd_panel;
  delete dev_panel;

  //---------------------------
}

//Main function
void Tab::create_panels(){
  //---------------------------

  rnd_panel->create_panels();
  dev_panel->create_panels();

  //---------------------------
}
void Tab::run_tab(){
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
void Tab::tabs(){
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
void Tab::draw_panels(){
  //---------------------------

  //Draw selected tab panels
  if(active_tab == "Render"){
    rnd_panel->draw_panels();
  }
  else if(active_tab == "Dev"){
    dev_panel->draw_panels();
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
