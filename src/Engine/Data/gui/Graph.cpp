#include "Graph.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Camera/Namespace.h>
#include <Operation/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::gui{

//Constructor / Destructor
Graph::Graph(dat::Node* node_data, bool* show_window){
  //---------------------------

  this->dat_graph = node_data->get_dat_graph();
  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();
  this->dat_struct = node_data->get_dat_struct();
  this->rnd_set = new dat::gui::Set(node_data, &show_panel_set);
  this->rnd_object = new dat::gui::Entity(node_data, &show_panel_entity);

  this->name = "Graph";
  this->show_window = show_window;

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::run_panel(){
  //---------------------------

  rnd_object->run_panel();
  rnd_set->run_panel();

  if(*show_window){
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 2.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(600, 600));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Graph::design_panel(){
  //---------------------------

  //this->draw_window_background();
  this->draw_file_tree();

  //---------------------------
}

//Subfunction
void Graph::draw_file_tree(){
  dat::base::Set* set_main = dat_graph->get_set_main();
  //---------------------------

  static ImGuiTableFlags flag;
  flag |= ImGuiTableFlags_NoBordersInBody;
  flag |= ImGuiTableFlags_SizingFixedSame;
  flag |= ImGuiTableFlags_RowBg;

  ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);
  ImGui::SetNextWindowSize(ImVec2(400, 400));
  ImGui::BeginTable("data_view", 2, flag);
  ImGui::TableSetupColumn("Name##scene_tree", ImGuiTableColumnFlags_WidthStretch);
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
int Graph::tree_set(dat::base::Set* set){
  int nb_row = 0;
  //---------------------------

  bool is_empty = dat_set->is_set_empty(set);
  if(set->is_suppressible && is_empty) return 0;

  //Set node elements
  ImGuiTreeNodeFlags flag;
  flag |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag |= set->is_open ? ImGuiTreeNodeFlags_DefaultOpen : 0;
  flag |= (set == dat_struct->selection) ? ImGuiTreeNodeFlags_Selected : 0;
  flag |= ImGuiTreeNodeFlags_SpanFullWidth;
  std::string name = set->icon + "   " + set->name;

  //Set row
  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  bool is_node_open = ImGui::TreeNodeEx(name.c_str(), flag);

  //If set is double-clicked, open set panel
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    rnd_set->set_selected_set(set);
    this->show_panel_set = true;
  }

  //Set selection
  if(ImGui::IsItemClicked()){
    dat_selection->select_element(set);
  }

  //Bin button
  ImGui::TableNextColumn();
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

  //If set open, display elements
  if(is_node_open){
    this->tree_set_open(set, nb_row);
    ImGui::TreePop();
  }

  //---------------------------
  return nb_row;
}
void Graph::tree_set_open(dat::base::Set* set, int& nb_row){
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
void Graph::tree_entity(dat::base::Set* set, dat::base::Entity* entity, int& nb_row){
  bool entity_selected = (entity == dat_struct->selection);
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
    rnd_object->set_entity(entity);
    this->show_panel_entity = true;
  }

  ImGui::TableNextColumn();
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
  std::string tag = std::string(ICON_FA_XMARK) + "##" + entity->name + std::to_string(nb_row);
  if(entity->is_suppressible && ImGui::SmallButton(tag.c_str())){
    dat_set->remove_entity(set, entity);
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}
void Graph::draw_window_background(int nb_row){
  //-------------------------------

  // Get window dimensions and position
  ImVec2 content_size = ImGui::GetWindowContentRegionMax(); // Available content size in the window
  float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
  float line_height = ImGui::GetTextLineHeightWithSpacing();
  int row_count = static_cast<int>((content_size.y - item_spacing_y) / line_height) - 2;
  row_count = row_count - nb_row;

  // Ensure the table fills the entire height
  for (int i = 0; i < row_count; i++){
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text(" ");
  }

  //-------------------------------
}

}
