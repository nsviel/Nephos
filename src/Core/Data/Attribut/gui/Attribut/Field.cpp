#include "Field.h"

#include <Data/Attribut/Namespace.h>
#include <Data/Element/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::atr::gui{

//Constructor / Destructor
Field::Field(dat::atr::Node* node_attribut){
  //---------------------------

  this->atr_struct = node_attribut->get_atr_struct();
  this->dat_element = new dat::elm::Element();
  this->atr_field = new dat::atr::field::Manager();
  this->ope_field = new dat::atr::field::Operation();

  //---------------------------
}
Field::~Field(){}

//Main function
void Field::design_header(std::shared_ptr<utl::base::Element> element){
  if(!element) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Field##attribut")){
    std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
    if(!entity) return;

    this->draw_selection(entity);
    this->draw_parameter(entity);
  }

  //---------------------------
}

//Subfunction
void Field::draw_selection(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  std::vector<std::string> vec_name = atr_field->get_field_names(*entity->data);
  glm::vec2 range = atr_field->get_field_range(*entity->data, selected_field);

  //Field selection table
  static int selection = 0;
  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_Borders;
  ImGui::PushStyleColor(ImGuiCol_TableRowBg, IM_COL32(0, 0, 0, 255));
  if(ImGui::BeginTable("##attribut_field", 3, flags)){
    ImGui::TableSetupColumn("Column 1", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("Column 2", ImGuiTableColumnFlags_WidthFixed, 50.0f);
    ImGui::TableSetupColumn("Column 3", ImGuiTableColumnFlags_WidthFixed, 50.0f);

    // Iterate over the vector of names to populate the table
    for(int i = 0; i < vec_name.size(); ++i){
      std::string& name = vec_name[i];

      // Start a new row
      ImGui::TableNextRow(); ImGui::TableNextColumn();

      // Second column: display the name with selectable functionality
      const bool is_selected = (selection == i);
      if(ImGui::Selectable(name.c_str(), is_selected, ImGuiSelectableFlags_SpanAllColumns)){
        this->selected_field = name;
        selection = i;
      }

      ImGui::TableNextColumn();
      ImGui::Text("%.2f", range.x);

      ImGui::TableNextColumn();
      ImGui::Text("%.2f", range.y);

      if(is_selected){
        ImGui::SetItemDefaultFocus(); // Ensure the selected item is focused
      }
    }

    ImGui::EndTable();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Field::draw_parameter(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Normalize##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    ope_field->normalize_field(*entity->data, selected_field);
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}

}
