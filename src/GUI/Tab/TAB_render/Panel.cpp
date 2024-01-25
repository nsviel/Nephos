#include "Panel.h"

#include <GUI/Node.h>
#include <image/IconsFontAwesome6.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Operation/Namespace.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Panel::Panel(gui::Node* gui){
  //---------------------------

  this->gui = gui;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::create_panels(){
  //---------------------------

  this->rnd_option = new gui::rnd::tab::Option(gui, &show_option, "Option");
  this->rnd_menu = new gui::rnd::tab::Menu(this);

  //---------------------------
}
void Panel::draw_panels(){
  //---------------------------

  rnd_menu->run_tab_menu();
  rnd_option->run_panel();


  //---------------------------
}
void Panel::open_panels(){
  //---------------------------

  ImGui::Checkbox(ICON_FA_FOLDER " Loader##456", &show_loader);
  ImGui::Checkbox(ICON_FA_COG " Option##456", &show_option);
  ImGui::Checkbox(ICON_FA_PLAY " Scene##456", &show_scene);
  ImGui::Checkbox(ICON_FA_ARROW_ROTATE_RIGHT " Profiler##456", &show_profiler);
  ImGui::Checkbox(ICON_FA_CAMERA " Camera##456", &show_camera);
  ImGui::Checkbox(ICON_FA_ROAD " Shader##456", &show_shader);
  ImGui::Checkbox(ICON_FA_FILM " Kinect##456", &show_kinect);

  //---------------------------
}

}
