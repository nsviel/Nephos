#include "Menu.h"

#include <Engine/Namespace.h>
#include <GUI/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Menu::Menu(gui::rnd::tab::Panel* rnd_panel){
  //---------------------------

  this->rnd_panel = rnd_panel;

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
    rnd_panel->show_loader = !rnd_panel->show_loader;
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}


}
