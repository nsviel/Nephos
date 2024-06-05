#include "Panel.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Panel::Panel(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  this->gui_player = new dyn::gui::Player(node_dynamic);
  this->gui_operation = new dyn::gui::Operation(node_dynamic);

  this->show_window = show_window;
  this->name = "Panel";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(250, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  //---------------------------

  gui_player->design_player();
  gui_operation->design_operation();

  //---------------------------
}

}
