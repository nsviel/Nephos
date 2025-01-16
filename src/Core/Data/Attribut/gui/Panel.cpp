#include "Panel.h"

#include <Data/Attribut/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::atr::gui{

//Constructor / Destructor
Panel::Panel(dat::atr::Node* node_attribut, bool* show_window){
  //---------------------------

  dat::gph::Node* node_graph = node_attribut->get_node_graph();

  this->gui_color = new dat::atr::gui::Color(node_attribut);
  this->gui_normal = new dat::atr::gui::Normal(node_attribut);
  this->gui_field = new dat::atr::gui::Field(node_attribut);
  this->gph_selection = node_graph->get_gph_selection();
  this->dat_element = new dat::elm::Element();
  this->atr_field = new dat::atr::Field();

  this->show_window = show_window;
  this->panel_name = "Attribut";
  this->item_width = 100;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(panel_name.c_str(), show_window, flag) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  //---------------------------

  this->enum_data(element);
  gui_normal->design_header(element);
  gui_color->design_header(element);
  gui_field->design_header(element);

  //---------------------------
}

//Subfunction
void Panel::enum_data(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  std::vector<std::string> vec_name = atr_field->get_field_names(*entity->data);
  bool has_normal = (entity->data->Nxyz.size() != 0);
  bool has_color = (entity->data->rgb.size() != 0);
  int size = 1 + (has_normal ? 1 : 0) + (has_color ? 1 : 0) + vec_name.size();

  ImGui::PushStyleColor(ImGuiCol_TableRowBg, IM_COL32(0, 0, 0, 255));
  ImGui::PushStyleColor(ImGuiCol_TableRowBgAlt, IM_COL32(0, 0, 0, 255));
  ImGui::BeginTable("OneLineTable", size, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchSame);
  ImGui::TableNextRow();

  //Location
  ImGui::TableNextColumn();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "XYZ");

  //Normal
  if(has_normal){
    ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "Nxyz");
  }

  //Color
  if(has_color){
    ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "RGB");
  }

  //Field
  for(auto& name : vec_name){
    ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", name.c_str());
  }

  ImGui::EndTable();
  ImGui::PopStyleColor(2);

  //---------------------------
}

}
