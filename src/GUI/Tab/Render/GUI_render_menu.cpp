#include "GUI_render_menu.h"

#include <GUI.h>
#include <Tab/GUI_tab.h>
#include <Tab/Render/GUI_render.h>
#include <Tab/Render/GUI_render_panel.h>
#include <Data/Data.h>
#include <Data/Load/Loader.h>
#include <Tab/Render/GUI_render_option.h>
#include <image/IconsFontAwesome5.h>
#include <Render/Initialization/GUI_init.h>


//Constructor / Destructor
GUI_render_menu::GUI_render_menu(GUI* gui){
  //---------------------------

  Data* data = gui->get_data();
  GUI_tab* gui_tab = gui->get_gui_tab();
  this->gui = gui;
  this->gui_init = gui->get_gui_init();
  this->gui_render = gui_tab->get_gui_render();
  this->gui_render_option = gui_render->get_gui_option();
  this->gui_render_panel = gui_render->get_render_panel();
  this->loaderManager = data->get_loaderManager();

  this->show_demo = false;

  //---------------------------
}
GUI_render_menu::~GUI_render_menu(){}

//Main function
void GUI_render_menu::design_menubar(){
  //------------------------

  ImGui::BeginMainMenuBar();
  this->menu();
  ImGui::EndMainMenuBar();

  //-------------------------
}

//Subfunctions
void GUI_render_menu::menu(){
  //---------------------------

  if(ImGui::BeginMenu("Panel##111")){
    gui_render->open_panels();
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Load")){
    loaderManager->load_by_zenity();
  }
  if(ImGui::BeginMenu("Init")){
    gui_init->design_init();
    ImGui::EndMenu();
  }

  //---------------------------
}
