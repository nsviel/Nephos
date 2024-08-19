#include "Button.h"

#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::gph::gui{

//Constructor / Destructor
Button::Button(dat::gph::Node* node_graph){
  //---------------------------

  dat::elm::Node* node_element = node_graph->get_node_element();

  this->dat_set = node_element->get_dat_set();
  this->dat_entity = node_element->get_dat_entity();

  //---------------------------
}
Button::~Button(){}

//Main function
void Button::button_locked(dat::base::Set* set){
  //---------------------------

  if(set->is_suppressible){
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

    if(set->is_locked){
      if(ImGui::SmallButton(ICON_FA_LOCK "##tree_set")){
        set->is_locked = false;
      }
    }else{
      if(ImGui::SmallButton(ICON_FA_UNLOCK "##tree_set")){
        set->is_locked = true;
      }
    }

    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Button::button_visibility(dat::base::Set* set){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

  //Is is visible
  if(set->is_visible){
    std::string tag = std::string(ICON_FA_EYE) + "##" + std::to_string(set->UID);
    if(ImGui::SmallButton(tag.c_str())){
      dat_set->visibility_set(set, false);
    }
  }
  //If not visible
  else{
    std::string tag = std::string(ICON_FA_EYE_SLASH) + "##" + std::to_string(set->UID);
    if(ImGui::SmallButton(tag.c_str())){
      dat_set->visibility_set(set, true);
    }
  }

  ImGui::PopStyleColor(3);

  //---------------------------
}
void Button::button_visibility(dat::base::Entity* entity){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

  //Is is visible
  if(entity->data.is_visible){
    std::string label = std::string(ICON_FA_EYE) + "##" + std::to_string(entity->UID);
    if(ImGui::SmallButton(label.c_str())){
      dat_entity->visibility_entity(entity, false);
    }
  }
  //If not visible
  else{
    std::string label = std::string(ICON_FA_EYE_SLASH) + "##" + std::to_string(entity->UID);
    if(ImGui::SmallButton(label.c_str())){
      dat_entity->visibility_entity(entity, true);
    }
  }

  ImGui::PopStyleColor(3);

  //---------------------------
}
void Button::button_remove(dat::base::Set* set, dat::base::Entity* entity){
  if(set->is_locked) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

  std::string tag = std::string(ICON_FA_XMARK) + "##" + std::to_string(entity->UID);
  if(entity->is_suppressible && ImGui::SmallButton(tag.c_str())){
    dat_set->remove_entity(set, entity);
  }

  ImGui::PopStyleColor(3);

  //---------------------------
}
void Button::button_remove(dat::base::Set* set){
  if(set->is_locked) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

  std::string tag = std::string(ICON_FA_XMARK) + "##" + std::to_string(set->UID);
  if(ImGui::SmallButton(tag.c_str())){
    dat_set->remove_all_entity(set);
  }

  ImGui::PopStyleColor(3);

  //---------------------------
}

}
