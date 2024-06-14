#include "Panel.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::gui::transformation{

//Constructor / Destructor
Panel::Panel(ldr::Node* node_loader, bool* show_window) : ldr::gui::Navigator(node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();

  this->name = "Transformation##555";
  this->show_window = show_window;
  this->with_bookmark = true;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
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

  this->draw_header();
  ImGui::Separator();
  this->draw_navigator();

  //---------------------------
}

//Subfunction
void Panel::draw_header(){
  //---------------------------


  //---------------------------
}

}
