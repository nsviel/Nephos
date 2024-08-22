#include "Set.h"

#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


namespace dat::gph::gui{

//Constructor / Destructor
Set::Set(dat::gph::Node* node_graph){
  //---------------------------

  dat::elm::Node* node_element = node_graph->get_node_element();

  this->gph_selection = node_graph->get_gph_selection();
  this->gui_set = node_element->get_gui_set();
  this->gui_button = new dat::gph::gui::Button(node_graph);
  this->gui_entity = new dat::gph::gui::Entity(node_graph);

  //---------------------------
}
Set::~Set(){}

//Main function
int Set::tree_set(dat::base::Set* set){
  bool node_open;
  int nb_row = 0;
  //---------------------------

  this->draw_node(set, node_open);
  this->draw_click(set);
  this->draw_button(set);
  this->draw_open(set, node_open, nb_row);

  //---------------------------
  return nb_row;
}

//Subfunction
void Set::draw_node(dat::base::Set* set, bool& node_open){
  utl::base::Element* element = gph_selection->get_selected_element();
  //---------------------------

  //Set node elements
  ImGuiTreeNodeFlags flag;
  flag |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag |= set->is_open ? ImGuiTreeNodeFlags_DefaultOpen : 0;
  flag |= (set == element) ? ImGuiTreeNodeFlags_Selected : 0;
  flag |= ImGuiTreeNodeFlags_SpanFullWidth;
  std::string name = set->icon + "   " + set->name;

  //Set row
  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  node_open = ImGui::TreeNodeEx(name.c_str(), flag);

  //---------------------------
}
void Set::draw_click(dat::base::Set* set){
  //---------------------------

  //If set is double-clicked, open set panel
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    gui_set->set_selected_set(set);
    gui_set->show_panel(true);
  }

  //Set selection
  if(ImGui::IsItemClicked()){
    gph_selection->select_element(set);
  }

  //---------------------------
}
void Set::draw_button(dat::base::Set* set){
  //---------------------------

  //Visibility button
  ImGui::TableNextColumn();
  gui_button->button_visibility(set);

  //Remove button
  ImGui::TableNextColumn();
  gui_button->button_remove(set);

  //---------------------------
}
void Set::draw_open(dat::base::Set* set, bool& node_open, int& nb_row){
  //---------------------------

  //If set open, display elements
  if(node_open){
    //List all direct entities
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      gui_entity->tree_entity(set, entity, nb_row);
    }

    //Recursive call for nested sets
    if(set == nullptr) return;
    for(dat::base::Set* subset : set->list_subset){
      nb_row += tree_set(subset);
    }

    ImGui::TreePop();
  }

  //---------------------------
}

}
