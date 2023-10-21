#include "GUI_mainmenubar.h"
#include "GUI_option.h"
#include "../../Element/Initialization/GUI_init.h"

#include <GUI.h>
#include <Tab/GUI_tab.h>
#include <Tab/Render/GUI_render_panel.h>
#include <Tab/Render/Struct_render_panel.h>
#include <Data/Data.h>
#include <Data/Load/Loader.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
GUI_mainmenubar::GUI_mainmenubar(GUI* gui){
  //---------------------------

  Data* data = gui->get_data();
  GUI_tab* gui_tab = gui->get_gui_tab();
  this->gui = gui;
  this->gui_init = gui->get_gui_init();
  this->gui_render_panel = gui_tab->get_gui_render_panel();
  this->gui_option = gui_render_panel->get_gui_option();
  this->struct_render_panel = gui_render_panel->get_panel();
  this->loaderManager = data->get_loaderManager();

  this->show_demo = false;

  //---------------------------
}
GUI_mainmenubar::~GUI_mainmenubar(){}

//Main function
void GUI_mainmenubar::design_menubar(){
  //------------------------

  //ImGui::BeginMainMenuBar();
  this->menu();
  this->main_tab();
  //ImGui::EndMainMenuBar();

  //-------------------------
}

//Subfunctions
void GUI_mainmenubar::menu(){
  //---------------------------

  if(ImGui::MenuItem("Load")){
    loaderManager->load_by_zenity();
  }
  if(ImGui::BeginMenu("Init")){
    gui_init->design_init();
    ImGui::EndMenu();
  }
  if(ImGui::BeginMenu("Demo")){
    this->menu_demo();
    ImGui::EndMenu();
  }
  if(show_demo){
    ImGui::ShowDemoWindow(&show_demo);
  }
  if(ImGui::MenuItem(ICON_FA_COG, "Option")){
    struct_render_panel->show_option = !struct_render_panel->show_option;
  }
  if(ImGui::MenuItem(ICON_FA_CAMERA, "Camera##111")){
    struct_render_panel->show_camera = !struct_render_panel->show_camera;
  }
  if(ImGui::BeginMenu("Panel##111")){
    gui_render_panel->open_panels();
    ImGui::EndMenu();
  }

  //---------------------------
}
void GUI_mainmenubar::menu_demo(){
  //---------------------------

  //Demo file
  if(ImGui::Button("Demo file")){
    int ret = system("xed ../extern/imgui/core/imgui_demo.cpp");
  }

  //Demo window
  ImGui::Checkbox("Demo window", &show_demo);

  //---------------------------
}
void GUI_mainmenubar::main_tab(){
  //---------------------------

  if (ImGui::BeginTabBar("main_tab")){
    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Engine")){

        ImGui::EndTabItem();
    }
    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Dev")){

        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
