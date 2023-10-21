#include "GUI_tab.h"
#include "Render/GUI_render_panel.h"
#include "Render/Struct_render_panel.h"
#include "Dev/GUI_dev_panel.h"

#include <GUI.h>


//Constructor / Destructor
GUI_tab::GUI_tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->struct_render_panel = new Struct_render_panel();
  this->gui_render_panel = new GUI_render_panel(gui);
  this->gui_dev_panel = new GUI_dev_panel(gui);

  //---------------------------
}
GUI_tab::~GUI_tab(){
  //---------------------------

  delete gui_render_panel;
  delete gui_dev_panel;

  //---------------------------
}

//Main function
void GUI_tab::create_panels(){
  //---------------------------

  gui_render_panel->create_panels();
  gui_dev_panel->create_panels();

  //---------------------------
}
void GUI_tab::draw_tabs(){
  //---------------------------

  ImGui::BeginMainMenuBar();

  if (ImGui::BeginTabBar("main_tab")){
    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Render")){

      this->active_tab = "Render";
      ImGui::EndTabItem();
    }
    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Dev")){

      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  ImGui::EndMainMenuBar();

  if(active_tab == "Render"){
          gui_render_panel->draw_panels();
  }

  //---------------------------
}
