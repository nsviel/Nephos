#include "Tab.h"

#include <GUI/Namespace.h>
#include <Core/Namespace.h>
#include <Utility/Namespace.h>


namespace gui{

//Constructor / Destructor
Tab::Tab(gui::Node* node_gui){
  //---------------------------

  this->node_core = node_gui->get_node_core();

  this->gui_state = node_gui->get_gui_state();
  this->gui_demo = node_gui->get_gui_demo();
  this->gui_docking = new gui::Docking();
  this->menu_left = new gui::menu::Left(node_gui);
  this->menu_center = new gui::menu::Center(node_gui);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::loop(){
  //---------------------------

  this->draw_frame();
  this->draw_menu();
  this->draw_tab();

  //---------------------------
}

//Tab function
void Tab::draw_frame(){
  //---------------------------

  gui_state->loop();
  ImGui::NewFrame();
  gui_docking->loop();
  gui_demo->loop();

  //---------------------------
}
void Tab::draw_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();

  //Left menu
  menu_left->draw();

  //Center menu
  menu_center->draw();

  ImGui::EndMainMenuBar();

  //---------------------------
}
void Tab::draw_tab(){
  //---------------------------

  node_core->gui();


  //---------------------------
}

}
