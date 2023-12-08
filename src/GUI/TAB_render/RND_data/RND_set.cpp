#include "RND_set.h"

#include <GUI.h>
#include <TAB_render/RND_tab/RND_panel.h>
#include <ENG_operation/Transformation/Attribut.h>


namespace gui::rnd::panel{

//Constructor / Destructor
RND_set::RND_set(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->item_width = 150;

  //---------------------------
}
RND_set::~RND_set(){}

//Main function
void RND_set::design_panel(){
  //---------------------------

  this->set_info(set_selected);
  this->set_parameter(set_selected);

  //---------------------------
}

//Subfunction
void RND_set::set_info(data::Set* set){
  //---------------------------

  this->set_name("Set " + set->name);

  //---------------------------
}
void RND_set::set_parameter(data::Set* set){
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
