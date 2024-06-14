#include "Operation.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Operation::Operation(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_selection = node_data->get_dat_selection();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_operation = node_dynamic->get_ope_cloud();
  this->dyn_colorization = new dyn::gui::Colorization(node_dynamic);
  this->ope_operation = new ope::Operation();
  this->ope_normal = new ope::normal::KNN();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::design_operation(){
  utl::base::Element* element = dat_selection->get_selected_element();
  if(element == nullptr) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
  this->draw_op_info(element);
  this->draw_ope_transformation(element);

  dat::base::Set* set = dat_selection->get_selected_set();
  dyn_colorization->design_colorization(set);
  this->draw_ope_normal(set);
  ImGui::PopStyleColor();

  //---------------------------
  ImGui::Separator();
}

//Subfunction
void Operation::draw_op_info(utl::base::Element* element){
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)) return;
  //---------------------------
/*
  dat::base::Set* set = dynamic_cast<dat::base::Set*>(element);
  dyn::base::Player* player = &set->player;
  if(player == nullptr) return;

  if(ImGui::CollapsingHeader("Info##dynamic")){

    ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
    ImGui::BeginTable("master##playback_info", 3);
    //Duration
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", player->ts_duration);

    //FPS
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("FPS"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d fps", player->fps_cur);
    ImGui::SetNextItemWidth(50); ImGui::TableNextColumn();
    ImGui::SliderInt("##56765", &player->fps_qry, 1, 120);

    //Path data
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path"); ImGui::TableNextColumn();
    string path = (player->path.data != "") ? player->path.data : "(not defined)";
    ImGui::TextColored(color, "%s", path.c_str());

    //Size
    if(player->size != 0){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Size"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f Mo", player->size);
    }

    ImGui::EndTable();

    //Recording time
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Record"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", master->recorder.ts_rec);

    //Recording file size
    if(master->recorder.mode == dyn::recorder::MKV){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Size"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f Mo", master->recorder.file_size);
    }
  }

  }
*/
  //---------------------------
}
void Operation::draw_ope_transformation(utl::base::Element* element){
  utl::base::Pose* pose = &element->pose;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Transformation##dynamic")){

    //Button
    if(ImGui::Button("C##centerentity", ImVec2(20, 0))){
      ope_operation->center_object(element);
    }
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##xrotation")){
      ope_operation->make_rotation_X_90d(element, 1);
    }
    ImGui::SameLine();
    if(ImGui::Button("Save##transfomatrix", ImVec2(70, 0))){
      //utl::transformation::save_transformation_to_file(pose->model, pose->path);
    }
    ImGui::SameLine();
    if(ImGui::Button("Identity##transfomatrix", ImVec2(70, 0))){
      utl::transformation::make_transformation_identity(pose->model);
    }

    ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
    ImGui::BeginTable("transformation_info##dynamic", 2);

    //Path transfo
    if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Path"); ImGui::TableNextColumn();

      utl::base::Data* data = &entity->data;
      string path = (data->path.transformation == "") ? "(not defined)" : data->path.transformation;
      ImGui::TextColored(color, "%s", path.c_str());
    }

    ImGui::EndTable();

    //Model matrix
    ImVec2 width = ImGui::GetContentRegionAvail();
    mat4& model = pose->model;
    ImGui::Columns(4, "ModelMat");
    for(int i=0; i<4; i++){
      ImGui::Separator();
      for(int j=0;j<4;j++){
        ImGui::Text("%.3f", model[i][j]);
        ImGui::NextColumn();
      }
    }
    ImGui::Separator();
    ImGui::Columns(1);

  }

  //---------------------------
}
void Operation::draw_ope_normal(dat::base::Set* set){
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Normal##dynamic")){

    if(ImGui::Button("Compute##normal", ImVec2(100, 0))){
      utl::base::Data* data = &set->active_entity->data;
      ope_normal->compute_normal(data, dyn_struct->operation.normal.knn);
    }

    //Parameter: kNN
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("kNN", &dyn_struct->operation.normal.knn, 1, 10);

    //Computation time
    ImGui::Text("Time");
    ImGui::SameLine();
    ImGui::TextColored(color, "%.2f ms", dyn_struct->operation.normal.time);

  }

  //---------------------------
}

}
