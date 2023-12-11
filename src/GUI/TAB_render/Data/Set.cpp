#include "Set.h"

#include <Node/GUI.h>
#include <Engine/ENG_operation/Transformation/Attribut.h>


namespace gui::rnd::panel{

//Constructor / Destructor
Set::Set(GUI* gui, bool* show_window){
  //---------------------------

  this->panel_show = show_window;
  this->panel_name = "Set";
  this->item_width = 150;

  //---------------------------
}
Set::~Set(){}

//Main function
void Set::run_panel(){
  //---------------------------

  if(*panel_show){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
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
void Set::set_info(eng::structure::Set* set){
  //---------------------------

  this->panel_name = "Set " + set->name;

  //---------------------------
}
void Set::set_parameter(eng::structure::Set* set){
  ImGui::Columns(2);
  //---------------------------

  //Visibility
  ImGui::Text("Visibility");
  ImGui::NextColumn();
  if(ImGui::Checkbox("##4555", &set->is_visible)){
    //Setfunc setfunc;
    //setfunc.set_visibility(set, set->is_visible);
  }
  ImGui::NextColumn();

  //Name
  ImGui::SetColumnWidth(-1,75);
  ImGui::Text("Name");
  ImGui::NextColumn();
  static char str_n[256];
  strcpy(str_n, set->name.c_str());
  if(ImGui::InputText("##name", str_n, IM_ARRAYSIZE(str_n), ImGuiInputTextFlags_EnterReturnsTrue)){
    set->name = str_n;
  }
  ImGui::NextColumn();

  //Number of object
  ImGui::Text("Nb object");
  ImGui::NextColumn();
  string nb_object = math::thousand_separator(set->nb_object);
  ImGui::Text("%s", nb_object.c_str());
  ImGui::NextColumn();

  //---------------------------
  ImGui::Columns(1);
}

}
