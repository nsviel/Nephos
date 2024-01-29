#include "Tab.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::gui{

//Constructor / Destructor
Tab::Tab(eng::Node* node_engine){
  //---------------------------

  this->gui_option = new eng::gui::Option(node_engine, &show_option);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::draw_tab(){
  //---------------------------

  this->draw_menu();
  gui_option->run_panel();

  //---------------------------
}

//Subfunction
void Tab::draw_menu(){
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
