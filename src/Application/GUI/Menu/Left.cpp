#include "Left.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace gui::menu{

//Constructor / Destructor
Left::Left(gui::Node* node_gui){
  //---------------------------

  this->gui_demo = node_gui->get_gui_demo();
  this->gui_font = node_gui->get_gui_font();
  this->gui_state = node_gui->get_gui_state();

  //---------------------------
}
Left::~Left(){}

//Menu function
void Left::menu(){
  //---------------------------

  //this->menu_font();
  this->menu_imgui();

  //---------------------------
}

//Subfunction
void Left::menu_font(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_GEAR, "menu_font")){
    gui_font->combo_font_gui();
    gui_font->combo_font_editor();
    ImGui::EndMenu();
  }

  //---------------------------
}
void Left::menu_imgui(){
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_BOOK, "menu_imgui")){
    gui_demo->gui();
    gui_state->gui();

    ImGui::EndMenu();
  }

  //---------------------------
}

}
