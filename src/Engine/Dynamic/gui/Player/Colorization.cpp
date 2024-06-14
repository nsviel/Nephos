#include "Colorization.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Colorization::Colorization(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_selection = node_data->get_dat_selection();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_operation = node_dynamic->get_ope_cloud();
  this->ope_operation = new ope::Operation();
  this->ope_normal = new ope::normal::KNN();

  //---------------------------
}
Colorization::~Colorization(){}

//Main function
void Colorization::design_colorization(dat::base::Set* set){
  dat::base::Entity* entity = set->active_entity;
  if(entity == nullptr) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Colorization##dynamic")){

    //Colorization mode
    ImGui::BeginTable("colorization##mode", 2);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    this->mode_rgb(entity);
    ImGui::TableNextColumn();
    this->mode_unicolor(entity);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    this->mode_intensity(entity);
    ImGui::TableNextColumn();
    this->mode_intensity_inv(entity);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    this->mode_normal(entity);
    ImGui::TableNextColumn();
    this->mode_normal(entity);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    this->mode_heatmap(entity);
    ImGui::TableNextColumn();
    this->mode_structure(entity);

    ImGui::EndTable();

    this->draw_option(entity);
  }

  //---------------------------
}

//Subfunction
void Colorization::mode_rgb(dat::base::Entity* entity){
  //---------------------------

  bool condition = (entity->data.rgb.size() == 0);
  if(condition) ImGui::BeginDisabled();
  if(ImGui::RadioButton("RGB##colorization", &dyn_struct->colorization.color_mode, ope::color::RGB)){
    this->update_color = true;
  }
  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Colorization::mode_unicolor(dat::base::Entity* entity){
  //---------------------------

  if(ImGui::RadioButton("##unicolor", &dyn_struct->colorization.color_mode, ope::color::UNICOLOR)){
    this->update_color = true;
  }
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("##unicolor_choice", (float*)&dyn_struct->colorization.unicolor, flags)){
    this->update_color = true;
  }

  //---------------------------
}
void Colorization::mode_intensity(dat::base::Entity* entity){
  //---------------------------

  bool condition = (entity->data.Is.size() == 0);
  if(condition) ImGui::BeginDisabled();
  if(ImGui::RadioButton("I##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY)){
    this->update_color = true;
  }
  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Colorization::mode_intensity_inv(dat::base::Entity* entity){
  //---------------------------

  bool condition = (entity->data.Is.size() == 0);
  if(condition) ImGui::BeginDisabled();
  if(ImGui::RadioButton("I##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY)){
    this->update_color = true;
  }
  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Colorization::mode_normal(dat::base::Entity* entity){
  //---------------------------

  bool condition = (entity->data.Nxyz.size() == 0);
  if(condition) ImGui::BeginDisabled();
  if(ImGui::RadioButton("N##colorization", &dyn_struct->colorization.color_mode, ope::color::NORMAL)){
    this->update_color = true;
  }
  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Colorization::mode_heatmap(dat::base::Entity* entity){
  //---------------------------

  if(ImGui::RadioButton("Heatmap##colorization", &dyn_struct->colorization.color_mode, ope::color::HEATMAP)){
    update_color = true;
  }

  //---------------------------
}
void Colorization::mode_structure(dat::base::Entity* entity){
  //---------------------------

  if(ImGui::RadioButton("Structure##colorization", &dyn_struct->colorization.color_mode, ope::color::STRUCTURE)){
    update_color = true;
  }

  //---------------------------
}
void Colorization::draw_option(dat::base::Entity* entity){
  //---------------------------

  //Intensity cursor
  if(dyn_struct->colorization.color_mode == ope::color::INTENSITY){
    ImGui::Separator();
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("I diviser", &dyn_struct->operation.intensity.diviser, 1, 10000);
  }

  //Heatmap mode
  if(dyn_struct->colorization.color_mode == ope::color::HEATMAP){
    ImGui::Separator();
    bool condition = (entity->data.Is.size() == 0);
    if(condition) ImGui::BeginDisabled();
    if(ImGui::RadioButton("I##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INTENSITY)){
      update_color = true;
    }
    if(condition) ImGui::EndDisabled();
    ImGui::SameLine();
    if(ImGui::RadioButton("H##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::HEIGHT)){
      update_color = true;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("R##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::RANGE)){
      update_color = true;
    }

    //Intensity heatmap
    if(dyn_struct->colorization.heatmap_mode == ope::color::heatmap::INTENSITY){
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("I diviser", &dyn_struct->operation.intensity.diviser, 1, 10000);
    }

    //Height heatmap
    if(dyn_struct->colorization.heatmap_mode == ope::color::heatmap::HEIGHT){
      float min = -10;
      float max = 10;
      ImGui::SetNextItemWidth(125);
      ImGui::DragFloatRange2("Z##321", &dyn_struct->colorization.range_height.x, &dyn_struct->colorization.range_height.y, 0.1f, min, max, "%.1f", "%.1f");
    }
  }

  if(update_color){
    dyn_operation->colorize_object(entity);
    //dyn_operation->update_object(entity);
  }

  //---------------------------
}



}
