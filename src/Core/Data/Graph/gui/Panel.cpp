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

  this->dat_graph = node_graph->get_gph_graph();
  this->gui_set = new dat::gph::gui::Set(node_graph);

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

    ImGui::PushID(set->name.c_str());
    nb_row += gui_set->tree_set(set) + 1;
    ImGui::PopID();
  }

  this->draw_window_background(nb_row);

  ImGui::EndTable();
  ImGui::PopStyleVar();

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
