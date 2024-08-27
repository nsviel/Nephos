#include "Entity.h"

#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


namespace dat::gph::gui{

//Constructor / Destructor
Entity::Entity(dat::gph::Node* node_graph){
  //---------------------------

  dat::elm::Node* node_element = node_graph->get_node_element();

  this->gph_selection = node_graph->get_gph_selection();
  this->gui_button = new dat::gph::gui::Button(node_graph);
  this->gui_entity = node_element->get_gui_entity();

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::tree_entity(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity, int& nb_row){
  //---------------------------

  this->draw_leaf(set, entity);
  this->draw_click(entity);
  this->draw_button(set, entity);

  //---------------------------
  nb_row++;
}

//Subfunction
void Entity::draw_leaf(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  std::shared_ptr<utl::base::Element> selection = gph_selection->get_selected_element();
  bool entity_selected = (entity->UID == selection->UID);
  bool entity_active = (entity == set->active_entity.lock());

  //Entity row element
  ImGuiTreeNodeFlags flag;
  flag |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
  flag |= ImGuiTreeNodeFlags_Leaf;
  flag |= ImGuiTreeNodeFlags_NoTreePushOnOpen;
  flag |= ImGuiTreeNodeFlags_SpanFullWidth;
  flag |= (entity_selected  && entity->is_suppressible) ? ImGuiTreeNodeFlags_Selected : 0;
  std::string icon = ICON_FA_FILE;
  std::string name = icon + "   " + entity->name;

  /*if(entity_active){
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.4f, 0.4f, 1.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.4f, 0.4f, 1.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.4f, 0.4f, 1.0f, 0.5f));
  }*/

  // Display leaf
  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  ImGui::TreeNodeEx(name.c_str(), flag);

  /*if(entity_active || entity_selected){
    ImGui::PopStyleColor(3);
  }*/

  //---------------------------
}
void Entity::draw_click(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  // If entity clicked
  if(ImGui::IsItemClicked()){
    gph_selection->select_element(entity);
  }

  // If entity double-clicked
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    gui_entity->set_entity(entity);
    gui_entity->show_panel(true);
  }

  //---------------------------
}
void Entity::draw_button(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  //Visibility button
  ImGui::TableNextColumn();
  gui_button->button_visibility(entity);

  //Supression button
  ImGui::TableNextColumn();
  gui_button->button_remove(set, entity);

  //---------------------------
}

}
