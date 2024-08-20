#include "Panel.h"

#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Core/Namespace.h>
#include <Engine/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


namespace dat::gph::gui{

//Constructor / Destructor
Panel::Panel(dat::gph::Node* node_graph, bool* show_window){
  //---------------------------

  dat::elm::Node* node_element = node_graph->get_node_element();

  this->dat_graph = node_graph->get_dat_graph();
  this->dat_selection = node_graph->get_dat_selection();
  this->dat_set = node_element->get_dat_set();
  this->gui_button = new dat::gph::gui::Button(node_graph);
  this->gui_set = node_element->get_gui_set();
  this->gui_entity = node_element->get_gui_entity();

  this->name = "Graph";
  this->show_window = show_window;

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
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 2.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(600, 600));
    if(ImGui::Begin(name.c_str(), show_window, flag) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  //---------------------------

  //this->draw_window_background();
  this->draw_file_tree();

  //---------------------------
}

//Subfunction
void Panel::draw_file_tree(){
  dat::base::Set* set_main = dat_graph->get_set_main();
  //---------------------------

  static ImGuiTableFlags flag;
  flag |= ImGuiTableFlags_NoBordersInBody;
  flag |= ImGuiTableFlags_SizingFixedSame;
  flag |= ImGuiTableFlags_RowBg;

  ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);
  ImGui::SetNextWindowSize(ImVec2(400, 400));
  ImGui::BeginTable("data_view", 3, flag);
  ImGui::TableSetupColumn("Name##scene_tree", ImGuiTableColumnFlags_WidthStretch);
  ImGui::TableSetupColumn("Visibility##scene_tree", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 25);
  ImGui::TableSetupColumn("Bin##scene_tree", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 25);

  //Database
  int nb_row = 0;
  for(int row_i=0; row_i<set_main->list_subset.size(); row_i++){
    dat::base::Set* set = *next(set_main->list_subset.begin(), row_i);

    if(set->nb_entity != 0 || set->nb_subset != 0){
      ImGui::PushID(set->name.c_str());
      nb_row += tree_set(set) + 1;
      ImGui::PopID();
    }
  }

  this->draw_window_background(nb_row);

  ImGui::EndTable();
  ImGui::PopStyleVar();

  //---------------------------
}
int Panel::tree_set(dat::base::Set* set){
  int nb_row = 0;
  //---------------------------

  bool is_empty = dat_set->is_set_empty(set);
  if(set->is_suppressible && is_empty) return 0;
  utl::base::Element* element = dat_selection->get_selected_element();

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
  bool is_node_open = ImGui::TreeNodeEx(name.c_str(), flag);

  //If set is double-clicked, open set panel
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    gui_set->set_selected_set(set);
    gui_set->show_panel(true);
  }

  //Set selection
  if(ImGui::IsItemClicked()){
    dat_selection->select_element(set);
  }

  //Visibility button
  ImGui::TableNextColumn();
  gui_button->button_visibility(set);

  //Remove button
  ImGui::TableNextColumn();
  gui_button->button_remove(set);

  //If set open, display elements
  if(is_node_open){
    this->tree_set_open(set, nb_row);
    ImGui::TreePop();
  }

  //---------------------------
  return nb_row;
}
void Panel::tree_set_open(dat::base::Set* set, int& nb_row){
  //---------------------------

  //List all direct entities
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    this->tree_entity(set, entity, nb_row);
  }

  //Recursive call for nested sets
  for(dat::base::Set* subset : set->list_subset){
    nb_row += tree_set(subset);
  }

  //---------------------------
}
void Panel::tree_entity(dat::base::Set* set, dat::base::Entity* entity, int& nb_row){
  bool entity_selected = (entity == dat_selection->get_selected_element());
  bool entity_active = (entity == entity->set_parent->active_entity);
  //---------------------------

  nb_row++;

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

  // If entity clicked
  if(ImGui::IsItemClicked()){
    dat_selection->select_element(entity);
  }

  // If entity double-clicked
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    gui_entity->set_entity(entity);
    gui_entity->show_panel(true);
  }

  //Visibility button
  ImGui::TableNextColumn();
  gui_button->button_visibility(entity);

  //Supression button
  ImGui::TableNextColumn();
  gui_button->button_remove(set, entity);

  //---------------------------
}
void Panel::draw_window_background(int nb_row){
  //-------------------------------

  // Get window dimensions and position
  ImVec2 content_size = ImGui::GetWindowContentRegionMax(); // Available content size in the window
  float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
  float line_height = ImGui::GetTextLineHeightWithSpacing();
  int row_count = static_cast<int>((content_size.y - item_spacing_y) / line_height) - 2;
  row_count = row_count - nb_row;

  // Ensure the table fills the entire height
  for(int i = 0; i < row_count; i++){
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text(" ");
  }

  //-------------------------------
}

}
