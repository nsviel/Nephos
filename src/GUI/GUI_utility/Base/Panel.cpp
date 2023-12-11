#include "Panel.h"


namespace gui::base{

//Constructor / Destructor
Panel::Panel(bool* show_window, string name){
  //---------------------------

  this->show_window = show_window;
  this->item_width = 150;
  this->name = name;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

//Subfunction
void Panel::design_panel(){
  //---------------------------


  //---------------------------
}

}
