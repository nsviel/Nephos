#include "Tab.h"

#include <GUI/Namespace.h>
#include <Core/Namespace.h>
#include <Scene/Namespace.h>
#include <Utility/Namespace.h>


namespace gui{

//Constructor / Destructor
Tab::Tab(gui::Node* node_gui){
  //---------------------------

  this->node_scene = node_gui->get_node_scene();
  this->node_core = node_gui->get_node_core();

  this->menu_left = new gui::menu::Left(node_gui);
  this->menu_center = new gui::menu::Center(node_gui);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::loop(){
  //---------------------------

  //Draw main menu bar
  ImGui::BeginMainMenuBar();
  menu_left->menu();
  ImGui::Separator();
  this->draw_tab_menu();
  ImGui::Dummy(ImVec2(100.0f, 0.0f)); // empty space
  ImGui::EndMainMenuBar();
  
  this->draw_tab();

  //---------------------------
}

//Tab function
void Tab::draw_tab_menu(){
  ImGuiTabItemFlags flag;
  //---------------------------



  //---------------------------
}
void Tab::draw_tab(){
  //---------------------------

  node_scene->gui();
  node_core->gui();
  menu_center->draw();

  //---------------------------
}

}
