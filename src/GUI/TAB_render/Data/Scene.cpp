#include "Scene.h"

#include <Engine/Engine.h>
#include <Node/GUI.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <Engine/Data/Scene/Database.h>
#include <GUI/TAB_render/Data/Namespace.h>


namespace gui::rnd::panel{

//Constructor / Destructor
Scene::Scene(GUI* gui, gui::rnd::tab::Panel* tab_panel){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();
  this->eng_database = eng_data->get_eng_database();
  this->tab_panel = tab_panel;
  this->panel_set = new gui::rnd::panel::Set(gui, &tab_panel->show_set);
  this->panel_object = new gui::rnd::panel::Object(gui, &tab_panel->show_object);

  this->panel_show = &tab_panel->show_scene;

  //---------------------------
}
Scene::~Scene(){}

//Main function
void Scene::run_panel(){
  //---------------------------

  panel_object->run_panel();
  panel_set->run_panel();

  if(*panel_show){
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(200, 100), ImVec2(1000, 1000));
    if(ImGui::Begin("Scene", panel_show, ImGuiWindowFlags_AlwaysAutoResize)){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
  }

  //---------------------------
}
void Scene::design_panel(){
  //---------------------------

  this->draw_window_background();
  this->tree_view();

  //---------------------------
}

//Subfunction
void Scene::draw_window_background(){
  //-------------------------------

  float x1 = ImGui::GetCurrentWindow()->WorkRect.Min.x;
  float x2 = ImGui::GetCurrentWindow()->WorkRect.Max.x;
  float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
  float item_offset_y = -item_spacing_y * 0.1f;
  float line_height = ImGui::GetTextLineHeight() + item_spacing_y;
  int row_count = 50;
  ImU32 col_even = IM_COL32(35, 35, 35, 255);
  ImU32 col_odd = IM_COL32(25, 25, 25, 255);

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  float y0 = ImGui::GetCursorScreenPos().y + (float)(int)item_offset_y;

  int row_display_start;
  int row_display_end;
  ImGui::CalcListClipping(row_count, line_height, &row_display_start, &row_display_end);
  for (int row_n = row_display_start; row_n < row_display_end; row_n++)
  {
      ImU32 col = (row_n & 1) ? col_odd : col_even;
      if ((col & IM_COL32_A_MASK) == 0)
          continue;
      float y1 = y0 + (line_height * row_n);
      float y2 = y1 + line_height;
      draw_list->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
  }

  //-------------------------------
}
void Scene::tree_view(){
  list<eng::structure::Set*>* list_set = eng_database->get_list_set();
  //---------------------------

  static ImGuiTableFlags flag_tree;
  flag_tree |= ImGuiTableFlags_SizingFixedFit;
  flag_tree |= ImGuiTableFlags_NoBordersInBody;
  flag_tree |= ImGuiTableFlags_SizingFixedSame;

  ImGui::SetNextWindowSize(ImVec2(400, 400));
  if(ImGui::BeginTable("data_view", 1)){
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);

    //Database
    for(int row_i=0; row_i<list_set->size(); row_i++){
      eng::structure::Set* set = *next(list_set->begin(), row_i);

      if(set->nb_entity != 0){
        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::PushID(set->name.c_str());
        this->data_node_tree(set);
        ImGui::PopID();
      }
    }

    ImGui::EndTable();
  }

  //---------------------------
}
int Scene::data_node_tree(eng::structure::Set* set){
  int nb_row = 0;
  //-------------------------------

  //Node flag_tree
  ImGuiTreeNodeFlags flag_node;
  flag_node |= ImGuiTreeNodeFlags_OpenOnArrow;
  if(set->name != "Glyph"){
    flag_node |= ImGuiTreeNodeFlags_DefaultOpen;
  }

  //Leaf flag_tree
  ImGuiTreeNodeFlags flag_leaf;
  flag_leaf |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag_leaf |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
  flag_leaf |= ImGuiTreeNodeFlags_Leaf;
  flag_leaf |= ImGuiTreeNodeFlags_NoTreePushOnOpen;
  flag_leaf |= ImGuiTreeNodeFlags_Bullet;
  flag_leaf |= ImGuiTreeNodeFlags_SpanFullWidth;

  //Set nodes
  bool is_node_open = ImGui::TreeNodeEx(set->name.c_str(), flag_node);

  //If item double-clicked
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    panel_set->set_selected_set(set);
    tab_panel->show_set = true;
  }

  //Set elements leaf nodes
  if(is_node_open){
    for(int j=0; j<set->list_entity.size(); j++){
      eng::structure::Object* object = (eng::structure::Object*)*next(set->list_entity.begin(), j);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      nb_row++;

      //If object is selected
      eng::structure::Object* set_object = (eng::structure::Object*)set->selected_entity;
      if(object->ID == set_object->ID && set->name == "Scene"){
        flag_leaf |= ImGuiTreeNodeFlags_Selected;
      }else{
        flag_leaf &= ~ImGuiTreeNodeFlags_Selected;
      }

      //Display leaf
      ImGui::TreeNodeEx(object->name.c_str(), flag_leaf);

      //If item clicked
      if(ImGui::IsItemClicked()){
        set->selected_entity = object;
      }

      //If item double-clicked
      if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
        panel_object->set_selected_object(object);
        tab_panel->show_object = true;
      }

    }

    ImGui::TreePop();
  }

  //-------------------------------
  return nb_row;
}

}
