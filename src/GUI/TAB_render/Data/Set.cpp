#include "Set.h"

#include <GUI.h>
#include <Engine/Engine.h>


namespace gui::rnd::data{

//Constructor / Destructor
Set::Set(GUI* gui, bool* show_window){
  //---------------------------

  this->panel_show = show_window;
  this->panel_name = "Set";
  this->item_width = 100;

  //---------------------------
}
Set::~Set(){}

//Main function
void Set::run_panel(){
  //---------------------------

  if(*panel_show){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2, 0.2, 0.2, 1));
    if(ImGui::Begin(panel_name.c_str(), panel_show, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Set::design_panel(){
  //---------------------------

  this->set_info(set_selected);
  this->set_parameter(set_selected);

  //---------------------------
}

//Subfunction
void Set::set_info(utl::base::Set* set){
  //---------------------------

  this->panel_name = "[Set]  " + set->name;

  //---------------------------
}
void Set::set_parameter(utl::base::Set* set){
  //---------------------------

  if(ImGui::BeginTable("object##table", 2, ImGuiTableFlags_BordersInnerV)){
    //Visibility
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Visibility"); ImGui::TableNextColumn();
    if(ImGui::Checkbox("##4555", &set->is_visible)){
      set->set_visibility(set->is_visible);
    }

    //Name
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Name"); ImGui::TableNextColumn();
    static char str_n[256];
    strcpy(str_n, set->name.c_str());
    ImGui::SetNextItemWidth(item_width);
    if(ImGui::InputText("##name", str_n, IM_ARRAYSIZE(str_n), ImGuiInputTextFlags_EnterReturnsTrue)){
      set->name = str_n;
    }

    //Number of object
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Nb object"); ImGui::TableNextColumn();
    string nb_entity = math::thousand_separator(set->nb_entity);
    ImGui::Text("%s", nb_entity.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}

}
