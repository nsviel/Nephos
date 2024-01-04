#include "Loader.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <Engine/Data/Namespace.h>
#include <GUI/TAB_render/Tab/Init.h>
#include <imgui/dialog/ImDialog.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Loader::Loader(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();

  this->eng_loader = eng_data->get_eng_loader();
  this->current_dir = file::get_current_parent_path_abs();

  say(current_dir);

  //---------------------------
}
Loader::~Loader(){}

//Main function
void Loader::design_panel(){
  //---------------------------

  this->draw_header();
  this->draw_content();
  this->draw_footer();

  //---------------------------
}

//Subfunction
void Loader::draw_header(){
  //---------------------------

  //Point cloud scaling
  ImGui::SetNextItemWidth(100);
  ImGui::DragFloat("Scale##4567", &scale, 0.1, 0.1, 100, "%.2f x");
  ImGui::SameLine();

  //Remove old clouds
  ImGui::Checkbox("Remove##222", &remove_old);

  //---------------------------
}
void Loader::draw_content(){
  //---------------------------

  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_Resizable;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;
  if (ImGui::BeginTable("init_tree", 3, flags)){
    // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide, 175);
    ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75);
    ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75);
    ImGui::TableHeadersRow();


    ImGui::EndTable();
  }

  //---------------------------
}
void Loader::draw_footer(){
  //---------------------------



  //---------------------------
}

}
