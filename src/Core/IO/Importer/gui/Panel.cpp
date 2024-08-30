#include "Panel.h"

#include <IO/Importer/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp::gui{

//Constructor / Destructor
Panel::Panel(io::imp::Node* node_importer, bool* show_window){
  //---------------------------

  this->node_importer = node_importer;
  this->utl_navigator = new utl::gui::Navigator();
  this->gui_navigator = new io::imp::gui::Navigator(this);
  this->gui_bookmark = new io::imp::gui::Bookmark(this);
  this->gui_header = new io::imp::gui::Header(this);

  this->name = "Import##555";
  this->show_window = show_window;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    //Intial panel size
    static bool first_time = true;
    if(first_time){
      ImGui::SetNextWindowSize(ImVec2(400, 500));
      first_time = false;
    }

    //Panel
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, 500));
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

  //Header
  gui_header->draw_header();
  ImGui::Separator();

  //Tabs
  int width = ImGui::GetContentRegionAvail().x / 2;
  if(ImGui::BeginTabBar("Panel_tab##4567")){
    gui_navigator->draw_tab(width);
    gui_bookmark->draw_tab(width);

    ImGui::EndTabBar();
  }

  //---------------------------
}

}
