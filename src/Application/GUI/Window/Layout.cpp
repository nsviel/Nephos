#include "Layout.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>


namespace gui{

//Constructor / Destructor
Layout::Layout(gui::Node* node_gui){
  //---------------------------

  this->node_gui = node_gui;

  this->gui_state = node_gui->get_gui_state();
  this->gui_demo = node_gui->get_gui_demo();
  this->gui_docking = new gui::Docking();
  this->menu_left = new gui::menu::Left(node_gui);
  this->menu_center = new gui::menu::Center(node_gui);

  //---------------------------
}
Layout::~Layout(){}

//Main function
void Layout::loop(){
  //---------------------------

  this->draw_frame();
  this->draw_menu();
  this->draw_panel();

  //---------------------------
}

//Subfunction
void Layout::draw_frame(){
  //---------------------------

  gui_state->loop();
  ImGui::NewFrame();
  gui_docking->loop();
  gui_demo->loop();

  //---------------------------
}
void Layout::draw_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();

  //Left menu
  menu_left->draw();

  //Center menu
  menu_center->draw();

  ImGui::EndMainMenuBar();

  //---------------------------
}
void Layout::draw_panel(){
  //---------------------------

  node_gui->gui();

  //---------------------------
}

}
