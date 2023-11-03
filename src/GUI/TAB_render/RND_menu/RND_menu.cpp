#include "RND_menu.h"

#include <GUI.h>
#include <GUI_tab/GUI_tab.h>
#include <TAB_render/TAB_render.h>
#include <TAB_render/RND_config/RND_panel.h>
#include <Data/Data.h>
#include <Data/Load/Loader.h>
#include <TAB_render/RND_menu/RND_option.h>
#include <image/IconsFontAwesome5.h>
#include <TAB_render/RND_initialization/RND_init.h>


//Constructor / Destructor
RND_menu::RND_menu(GUI* gui){
  //---------------------------

  Data* data = gui->get_data();
  GUI_tab* gui_tab = gui->get_gui_tab();
  this->gui = gui;
  this->gui_init = gui->get_gui_init();
  this->gui_tab_render = gui_tab->get_gui_render();
  this->gui_render_option = gui_tab_render->get_gui_option();
  this->gui_render_panel = gui_tab_render->get_render_panel();
  this->loaderManager = data->get_loaderManager();

  this->show_demo = false;

  //---------------------------
}
RND_menu::~RND_menu(){}

//Main function
void RND_menu::run_tab_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    gui_tab_render->open_panels();
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Load")){
    loaderManager->load_by_zenity();
  }
  if(ImGui::BeginMenu("Init")){
    gui_init->design_init();
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}

//Subfunctions
