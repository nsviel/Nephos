#include "Panel.h"

#include <Data/Element/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::set::gui{

//Constructor / Destructor
Panel::Panel(dat::elm::Node* node_element){
  //---------------------------

  this->dat_set = node_element->get_dat_set();

  this->panel_show = false;
  this->panel_name = "Set";
  this->item_width = 100;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(panel_show){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2, 0.2, 0.2, 1));
    if(ImGui::Begin(panel_name.c_str(), &panel_show, flag) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  //---------------------------

  this->set_info(set_selected);
  this->set_parameter(set_selected);

  //---------------------------
}

//Subfunction
void Panel::set_info(dat::base::Set* set){
  //---------------------------

  this->panel_name = "[Set]  " + set->name;

  //---------------------------
}
void Panel::set_parameter(dat::base::Set* set){
  //---------------------------

  ImGui::BeginTable("object##table", 2, ImGuiTableFlags_BordersInnerV);
  //Visibility
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Visibility"); ImGui::TableNextColumn();
  if(ImGui::Checkbox("##4555", &set->is_visible)){
    dat_set->visibility_set(set, set->is_visible);
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

  //Entity number
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Nb entity"); ImGui::TableNextColumn();
  std::string nb_entity = math::thousand_separator(set->nb_entity);
  ImGui::Text("%s", nb_entity.c_str());

  //Number of object
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Nb point"); ImGui::TableNextColumn();
  int nb_point = dat_set->compute_number_point(set);
  std::string number = math::thousand_separator(nb_point);
  ImGui::Text("%s", number.c_str());

  ImGui::EndTable();

  //---------------------------
}

}
