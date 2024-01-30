#include "Scene.h"

#include <Engine/Node.h>
#include <Engine/Scene/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::scene::gui{

//Constructor / Destructor
Scene::Scene(eng::scene::Node* sce_node, bool* show_window){
  //---------------------------

  eng::Node* engine = sce_node->get_node_engine();
  eng::cam::Node* node_camera = engine->get_node_camera();

  this->sce_database = sce_node->get_scene_database();
  this->sce_scene = sce_node->get_scene();
  this->rnd_set = new eng::scene::gui::Set(&show_panel_set);
  this->rnd_object = new eng::scene::gui::Entity(sce_node, &show_panel_entity);
  this->cam_control = node_camera->get_camera_control();
  this->ope_operation = new eng::ope::Operation();

  this->name = "Scene";
  this->show_window = show_window;

  //---------------------------
}
Scene::~Scene(){}

//Main function
void Scene::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Scene::design_panel(){
  //---------------------------

  rnd_object->run_panel();
  rnd_set->run_panel();

  this->draw_button();
  this->draw_window_background();
  this->draw_file_tree();

  //---------------------------
}

//Subfunction
void Scene::draw_button(){
  utl::type::Set* set = sce_scene->get_selected_set();
  if(set == nullptr) return;
  //-------------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

  //Suppression
  if(ImGui::Button(ICON_FA_TRASH "##supressionentity")){
    if(set->is_locked){
      sce_scene->delete_set(set);
    }else if(set->is_locked){
      sce_scene->delete_scene_entity(set->selected_entity);
    }
  }

  //Centered
  ImGui::SameLine();
  if(ImGui::Button("C##centerentity", ImVec2(20, 0))){
    ope_operation->center_object(set);
  }

  //Rotation 90° around X axis
  ImGui::SameLine();
  if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##xrotation")){
    ope_operation->make_rotation_X_90d(set, 1);
  }

  //Camera mode
  ImGui::SameLine();
  if(ImGui::Button(ICON_FA_CAMERA "##camera123")){
    cam_control->set_next_camera_mode();
  }

  ImGui::PopStyleVar();
  ImGui::Separator();

  //-------------------------------
}
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
  for (int row_n = row_display_start; row_n < row_display_end; row_n++){
    ImU32 col = (row_n & 1) ? col_odd : col_even;
    if ((col & IM_COL32_A_MASK) == 0)
      continue;
    float y1 = y0 + (line_height * row_n);
    float y2 = y1 + line_height;
    draw_list->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
  }

  //-------------------------------
}
void Scene::draw_file_tree(){
  utl::type::Set* data_set = sce_database->get_data_set();
  //---------------------------

  static ImGuiTableFlags flag_tree;
  flag_tree |= ImGuiTableFlags_SizingFixedFit;
  flag_tree |= ImGuiTableFlags_NoBordersInBody;
  flag_tree |= ImGuiTableFlags_SizingFixedSame;

  ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);
  ImGui::SetNextWindowSize(ImVec2(400, 400));
  if(ImGui::BeginTable("data_view", 1)){
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);

    //Database
    for(int row_i=0; row_i<data_set->list_set.size(); row_i++){
      utl::type::Set* set = *next(data_set->list_set.begin(), row_i);

      if(set->nb_entity != 0 || set->nb_set != 0){
        ImGui::TableNextRow();
        ImGui::TableNextColumn();

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
int Scene::tree_set(utl::type::Set* set) {
  int nb_row = 0;
  //---------------------------

  if(set->nb_entity == 0) return 0;

  // Node flags
  ImGuiTreeNodeFlags flag_node;
  flag_node |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag_node |= set->name != "World" ? ImGuiTreeNodeFlags_DefaultOpen : 0;

  // Set nodes
  string name = set->icon + "   " + set->name;
  bool is_node_open = ImGui::TreeNodeEx(name.c_str(), flag_node);
  this->tree_set_double_click(set);
  if(is_node_open){
    this->tree_set_open(set, nb_row);
    ImGui::TreePop();
  }

  //---------------------------
  return nb_row;
}
void Scene::tree_set_double_click(utl::type::Set* set){
  //---------------------------

  // If set is double-clicked
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    rnd_set->set_selected_set(set);
    this->show_panel_set = true;
  }

  //---------------------------
}
void Scene::tree_set_open(utl::type::Set* set, int& nb_row){
  //---------------------------

  ImGuiTreeNodeFlags flag_leaf;
  flag_leaf |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag_leaf |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
  flag_leaf |= ImGuiTreeNodeFlags_Leaf;
  flag_leaf |= ImGuiTreeNodeFlags_NoTreePushOnOpen;
  flag_leaf |= ImGuiTreeNodeFlags_SpanFullWidth;

  for(int i=0; i<set->list_entity.size(); i++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), i);
    this->tree_entity(set, entity, nb_row);
  }

  // Recursive call for nested sets
  for(utl::type::Set* subset : set->list_set) {
    nb_row += tree_set(subset);
  }

  //---------------------------
}
void Scene::tree_entity(utl::type::Set* set, utl::type::Entity* entity, int& nb_row){
  utl::type::Set* set_scene = sce_scene->get_set_scene();
  //---------------------------

  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  nb_row++;

  ImGuiTreeNodeFlags flag_leaf;
  flag_leaf |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag_leaf |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
  flag_leaf |= ImGuiTreeNodeFlags_Leaf;
  flag_leaf |= ImGuiTreeNodeFlags_NoTreePushOnOpen;
  flag_leaf |= ImGuiTreeNodeFlags_SpanFullWidth;
  flag_leaf |= (set_scene->is_selected_entity(entity) && entity->is_suppressible) ? ImGuiTreeNodeFlags_Selected : 0;

  // Display leaf
  string icon = ICON_FA_FILE_O;
  string name = icon + "   " + entity->name;
  ImGui::TreeNodeEx(name.c_str(), flag_leaf);

  // If entity clicked
  if (ImGui::IsItemClicked()) {
    set_scene->set_selected_entity(entity);
  }

  // If entity double-clicked
  if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
    rnd_object->set_entity(entity);
    this->show_panel_entity = true;
  }

  //---------------------------
}

}
