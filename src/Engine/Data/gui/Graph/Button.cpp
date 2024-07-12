#include "Button.h"

#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::gui::graph{

//Constructor / Destructor
Button::Button(dat::Node* node_data){
  //---------------------------

  this->dat_set = node_data->get_dat_set();

  //---------------------------
}
Button::~Button(){}

//Main function
void Button::button_remove(dat::base::Set* set, dat::base::Entity* entity){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
  std::string tag = std::string(ICON_FA_XMARK) + "##" + std::to_string(entity->UID);
  if(entity->is_suppressible && ImGui::SmallButton(tag.c_str())){
    dat_set->remove_entity(set, entity);
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}

}
