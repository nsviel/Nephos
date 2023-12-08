#include "RND_menu.h"

#include <GUI.h>
#include <Engine.h>
#include <GUI_interface/GUI_tab.h>
#include <TAB_render/RND_tab/RND_tab.h>
#include <TAB_render/RND_tab/RND_panel.h>
#include <ENG_data/ENG_data.h>
#include <ENG_data/ENG_load/ENG_loader.h>
#include <TAB_render/RND_tab/RND_option.h>
#include <image/IconsFontAwesome5.h>
#include <TAB_render/RND_initialization/RND_init.h>


namespace gui::rnd::tab{

//Constructor / Destructor
RND_menu::RND_menu(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  ENG_data* eng_data = engine->get_eng_data();
  GUI_tab* gui_tab = gui->get_gui_tab();

  this->gui = gui;
  this->gui_init = new RND_init(gui);
  this->rnd_tab = gui_tab->get_rnd_tab();
  this->rnd_option = rnd_tab->get_rnd_option();
  this->rnd_panel = rnd_tab->get_rnd_panel();
  this->eng_loader = eng_data->get_eng_loader();

  //---------------------------
}
RND_menu::~RND_menu(){}

//Main function
void RND_menu::run_tab_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    rnd_tab->open_panels();
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Load")){
    eng_loader->load_by_zenity();
  }
  if(ImGui::BeginMenu("Init")){
    gui_init->design_init();
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}

//Subfunctions

}
