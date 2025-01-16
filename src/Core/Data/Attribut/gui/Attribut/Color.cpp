#include "Color.h"

#include <Data/Attribut/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::atr::gui{

//Constructor / Destructor
Color::Color(dat::atr::Node* node_attribut){
  //---------------------------

  this->atr_struct = node_attribut->get_atr_struct();
  this->atr_color = new dat::atr::Color(node_attribut);
  this->atr_field = new dat::atr::field::Manager();
  this->dat_element = new dat::elm::Element();

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::design_header(std::shared_ptr<utl::base::Element> element){
  if(!element) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Colorization##attribut")){
    this->color_mode(element);
    this->color_option(element);
  }

  //---------------------------
}

//Subfunction
void Color::color_mode(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  ImGui::BeginTable("colorization##mode", 2);

  //First line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  this->color_mode_rgb(element);
  ImGui::TableNextColumn();
  this->color_mode_unicolor(element);

  //Second line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  this->color_mode_normal(element);
  ImGui::TableNextColumn();
  this->color_mode_structure(element);

  //Third line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  this->color_mode_field(element);
  ImGui::TableNextColumn();
  this->color_mode_heatmap(element);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Color::color_mode_rgb(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data->rgb.size() == 0);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("RGB##colorization", &atr_struct->color.mode, dat::atr::color::RGB)){
    atr_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_mode_unicolor(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  if(ImGui::RadioButton("##unicolor", &atr_struct->color.mode, dat::atr::color::UNICOLOR)){
    atr_color->make_colorization(element);
  }
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("##unicolor_choice", (float*)&atr_struct->color.unicolor, flags)){
    atr_struct->color.mode = dat::atr::color::UNICOLOR;
    atr_color->make_colorization(element);
  }

  //---------------------------
}
void Color::color_mode_normal(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data->Nxyz.size() == 0);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("Nxyz##colorization", &atr_struct->color.mode, dat::atr::color::NORMAL)){
    atr_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_mode_field(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data->map_field.size() == 0);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("Field##colorization", &atr_struct->color.mode, dat::atr::color::FIELD)){
    atr_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_mode_heatmap(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data->map_field.size() == 0);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("Heatmap##colorization", &atr_struct->color.mode, dat::atr::color::HEATMAP)){
    atr_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_mode_structure(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data->width == -1);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("Structure##colorization", &atr_struct->color.mode, dat::atr::color::STRUCTURE)){
    atr_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_option(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  if(atr_struct->color.mode == dat::atr::color::FIELD || atr_struct->color.mode == dat::atr::color::HEATMAP){
    std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
    if(!entity) return;

    //Get vector of field names
    std::vector<std::string> vec_name = atr_field->get_field_names(*entity->data);

    //Init
    if(!entity->data->map_field.empty() && atr_struct->color.field == ""){
      atr_struct->color.field = vec_name[0];
      atr_struct->color.range = atr_field->get_field_range(*entity->data, vec_name[0]);
    }

    //Field selection table
    static int selection = 0;
    static ImGuiTableFlags flags;
    flags |= ImGuiTableFlags_RowBg;
    flags |= ImGuiTableFlags_Borders;
    ImGui::SetNextItemWidth(150);
    if(ImGui::BeginTable("##field_table", 1, flags)){
      // Iterate over the vector of names to populate the table
      for(int i = 0; i < vec_name.size(); ++i){
        std::string& name = vec_name[i];

        // Start a new row
        ImGui::TableNextRow(); ImGui::TableNextColumn();

        // Second column: display the name with selectable functionality
        const bool is_selected = (selection == i);
        if(ImGui::Selectable(name.c_str(), is_selected, ImGuiSelectableFlags_SpanAllColumns)){
          atr_struct->color.field = name;
          atr_struct->color.range = atr_field->get_field_range(*entity->data, name);
          selection = i;
        }

        if(is_selected){
          ImGui::SetItemDefaultFocus(); // Ensure the selected item is focused
        }
      }

      ImGui::EndTable();
    }

    //Range
    ImGui::SetNextItemWidth(150);
    glm::vec2 range = atr_field->get_field_range(*entity->data, atr_struct->color.field);
    float sensitivity = (range.y - range.x) / 100.0f;
    ImGui::DragFloatRange2("Range##321", &atr_struct->color.range.x, &atr_struct->color.range.y, sensitivity, range.x, range.y, "%.2f", "%.2f");
  }

  //---------------------------
}

}
