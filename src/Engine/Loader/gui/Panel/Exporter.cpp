#include "Exporter.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_loader, bool* show_window) : ldr::gui::Navigator(node_loader, false){
  //---------------------------

  this->name = "Exporter";
  this->show_window = show_window;

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::run_panel(){
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
void Exporter::design_panel(){
  //---------------------------

  this->draw_header();
  this->draw_navigator();

  //---------------------------
}

//Subfunction
void Exporter::draw_header(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  //filename
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::Button("Save##222")){
    this->item_operation();
    this->vec_selection.clear();
  }
  ImGui::TableNextColumn();
  static char str_n[256];
  strncpy(str_n, current_path.c_str(), sizeof(str_n) - 1);
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  if(ImGui::InputText("##exporter", str_n, IM_ARRAYSIZE(str_n))){
    this->current_path = str_n;
  }
  ImGui::PopStyleColor(2);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Exporter::item_operation(){
  //---------------------------

  //---------------------------
}

}
