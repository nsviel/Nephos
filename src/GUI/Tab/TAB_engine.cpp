#include "TAB_engine.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::tab{

//Constructor / Destructor
TAB_engine::TAB_engine(gui::Node* gui){
  //---------------------------

  this->gui = gui;

  //---------------------------
}
TAB_engine::~TAB_engine(){}

//Main function
void TAB_engine::init_tab(){
  //---------------------------

  this->rnd_option = new gui::rnd::tab::Option(gui, &show_option, "Option");

  //---------------------------
}
void TAB_engine::draw_tab(){
  //---------------------------

  this->draw_menu();
  rnd_option->run_panel();

  //---------------------------
}

//Subfunction
void TAB_engine::draw_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    ImGui::Checkbox(ICON_FA_COG " Option##456", &show_option);
    ImGui::Checkbox(ICON_FA_PLAY " Scene##456", &show_scene);
    ImGui::Checkbox(ICON_FA_ARROW_ROTATE_RIGHT " Profiler##456", &show_profiler);
    ImGui::Checkbox(ICON_FA_CAMERA " Camera##456", &show_camera);
    ImGui::Checkbox(ICON_FA_ROAD " Shader##456", &show_shader);
    ImGui::Checkbox(ICON_FA_FILM " Kinect##456", &show_kinect);
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Loader")){
    show_loader = !show_loader;
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}


}
