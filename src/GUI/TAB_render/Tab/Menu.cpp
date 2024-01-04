#include "Menu.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Menu::Menu(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();
  gui::Tab* gui_tab = gui->get_gui_tab();
  gui::rnd::tab::Tab* rnd_tab = gui_tab->get_rnd_tab();

  this->gui = gui;
  this->rnd_init = new gui::rnd::tab::Init(gui);
  this->rnd_loader = new gui::rnd::tab::Loader(gui);
  this->rnd_option = rnd_tab->get_rnd_option();
  this->rnd_panel = rnd_tab->get_rnd_panel();

  //---------------------------
}
Menu::~Menu(){}

//Main function
void Menu::run_tab_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    ImGui::Checkbox(ICON_FA_COG " Option##456", &rnd_panel->show_option);
    ImGui::Checkbox(ICON_FA_PLAY " Scene##456", &rnd_panel->show_scene);
    ImGui::Checkbox(ICON_FA_ARROW_ROTATE_RIGHT " Profiler##456", &rnd_panel->show_profiler);
    ImGui::Checkbox(ICON_FA_CAMERA " Camera##456", &rnd_panel->show_camera);
    ImGui::Checkbox(ICON_FA_ROAD " Shader##456", &rnd_panel->show_shader);
    ImGui::Checkbox(ICON_FA_FILM " Kinect##456", &rnd_panel->show_kinect);
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Load")){
    rnd_loader->loader_dialog();
  }
  if(ImGui::BeginMenu("Init")){
    rnd_init->design_init();
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  rnd_loader->loader_panel();

  //---------------------------
}


}
