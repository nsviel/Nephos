#include "Panel.h"

#include <Importer/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp::gui{

//Constructor / Destructor
Panel::Panel(io::imp::Node* node_importer, bool* show_window){
  //---------------------------

  this->node_importer = node_importer;
  this->gui_navigator = new io::imp::gui::Navigator(this);
  this->gui_bookmark = new io::imp::gui::Bookmark(this);
  this->gui_operation = new io::imp::gui::Operation(this);

  this->name = "Import##555";
  this->show_window = show_window;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, flag) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  //---------------------------

  gui_operation->draw_header();
  ImGui::Separator();
  int width = ImGui::GetContentRegionAvail().x / 2;
  if(ImGui::BeginTabBar("Panel_tab##4567")){
    gui_navigator->draw_tab(width);
    gui_bookmark->draw_tab(width);

    ImGui::EndTabBar();
  }

  //---------------------------
}

}
