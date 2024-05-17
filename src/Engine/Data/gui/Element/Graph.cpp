#include "Graph.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Camera/Namespace.h>
#include <Operation/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dat::gui{

//Constructor / Destructor
Graph::Graph(dat::Node* node_data, bool* show_window){
  //---------------------------

  this->dat_graph = node_data->get_data_graph();
  this->dat_set = node_data->get_data_set();
  this->dat_struct = node_data->get_data_struct();
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

  if(*show_window){
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Graph::design_panel(){
  //---------------------------

  rnd_object->run_panel();
  rnd_set->run_panel();

  this->draw_window_background();
  this->draw_file_tree();

  //---------------------------
}

//Subfunction
void Graph::draw_window_background(){
  //-------------------------------

  float x1 = ImGui::GetCurrentWindow()->WorkRect.Min.x;
  float x2 = ImGui::GetCurrentWindow()->WorkRect.Max.x;
  float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
  float item_offset_y = -item_spacing_y * 0.1f;
  float line_height = ImGui::GetTextLineHeight() + item_spacing_y;
  int row_count = 100;
  ImU32 col_even = IM_COL32(35, 35, 35, 255);
  ImU32 col_odd = IM_COL32(25, 25, 25, 255);

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  float y0 = ImGui::GetCursorScreenPos().y + (float)(int)item_offset_y;

  int row_display_start;
  int row_display_end;
  ImGui::CalcListClipping(row_count, line_height, &row_display_start, &row_display_end);
  for (int row_n = row_display_start; row_n < row_display_end; row_n++){
    ImU32 col = (row_n & 1) ? col_odd : col_even;
    if((col & IM_COL32_A_MASK) == 0)
      continue;
    float y1 = y0 + (line_height * row_n);
    float y2 = y1 + line_height;
    draw_list->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
  }

  //-------------------------------
}
void Graph::draw_file_tree(){
  dat::base::Set* set_main = dat_graph->get_set_main();
  //---------------------------

  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_SizingFixedFit;
  flags |= ImGuiTableFlags_NoBordersInBody;
  flags |= ImGuiTableFlags_SizingFixedSame;

  ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);
  ImGui::SetNextWindowSize(ImVec2(400, 400));
  if(ImGui::BeginTable("data_view", 2)){
    ImGui::TableSetupColumn("Name##scene_tree", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("Bin##scene_tree", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 25);

    //Database
    for(int row_i=0; row_i<set_main->list_subset.size(); row_i++){
      dat::base::Set* set = *next(set_main->list_subset.begin(), row_i);

      if(set->nb_entity != 0 || set->nb_subset != 0){
        ImGui::PushID(set->name.c_str());
        this->tree_set(set);
        ImGui::PopID();
      }
    }

    ImGui::EndTable();
  }
  ImGui::PopStyleVar();

  //---------------------------
}

//File tree
int Graph::tree_set(dat::base::Set* set){
  int nb_row = 0;
  //---------------------------

  bool is_empty = dat_set->is_set_empty(set);
  if(set->is_suppressible && is_empty) return 0;

  //Set node elements
  ImGuiTreeNodeFlags flags;
  flags |= ImGuiTreeNodeFlags_OpenOnArrow;
  flags |= set->is_open ? ImGuiTreeNodeFlags_DefaultOpen : 0;
  flags |= (set == dat_struct->selection) ? ImGuiTreeNodeFlags_Selected : 0;
  std::string name = set->icon + "   " + set->name;

  //Set row
  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  bool is_node_open = ImGui::TreeNodeEx(name.c_str(), flags);

  //If set is double-clicked, open set panel
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    rnd_set->set_selected_set(set);
    this->show_panel_set = true;
  }

  //Set selection
  if(ImGui::IsItemClicked()){
    dat_graph->select_element(set);
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
  //---------------------------

  nb_row++;

  //Entity row element
  ImGuiTreeNodeFlags flags;
  flags |= ImGuiTreeNodeFlags_OpenOnArrow;
  flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
  flags |= ImGuiTreeNodeFlags_Leaf;
  flags |= ImGuiTreeNodeFlags_NoTreePushOnOpen;
  flags |= ImGuiTreeNodeFlags_SpanFullWidth;
  flags |= (entity == dat_struct->selection && entity->is_suppressible) ? ImGuiTreeNodeFlags_Selected : 0;
  std::string icon = ICON_FA_FILE_O;
  std::string name = icon + "   " + entity->name;

  // Display leaf
  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  ImGui::TreeNodeEx(name.c_str(), flags);

  // If entity clicked
  if(ImGui::IsItemClicked()){
    dat_graph->select_element(entity);
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
    dat_set->remove(set, entity);
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}

}