#include "Colorization.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Colorization::Colorization(dyn::Node* node_dynamic){
  //---------------------------

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_operation = node_dynamic->get_ope_cloud();

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
    this->mode_intensity_cor(entity);
    ImGui::TableNextColumn();
    this->mode_intensity_cal(entity);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    this->mode_normal(entity);
    ImGui::TableNextColumn();
    this->mode_normal(entity);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    this->mode_heatmap(entity);
    ImGui::TableNextColumn();
    this->mode_structure(entity);

    ImGui::EndTable();

    ImGui::Separator();
    this->option_heatmap(entity);
    this->option_intensity(entity);
    this->option_height(entity);

    this->update_entity(entity);
  }

  //---------------------------
}
void Colorization::update_entity(dat::base::Entity* entity){
  //---------------------------

  if(update_color){
    dyn_operation->colorize_object(entity);
    //dyn_operation->update_object(entity);
    this->update_color = false;
  }

  //---------------------------
}

//Mode function
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
  if(ImGui::RadioButton("I inv##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_INV)){
    this->update_color = true;
  }
  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Colorization::mode_intensity_cor(dat::base::Entity* entity){
  //---------------------------

  bool condition = (entity->data.Is_cor.size() == 0);
  if(condition) ImGui::BeginDisabled();
  if(ImGui::RadioButton("I cor##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_COR)){
    this->update_color = true;
  }
  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Colorization::mode_intensity_cal(dat::base::Entity* entity){
  //---------------------------

  bool condition = (entity->data.Is_cal.size() == 0);
  if(condition) ImGui::BeginDisabled();
  if(ImGui::RadioButton("I cal##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_CAL)){
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

//Option function
void Colorization::option_heatmap(dat::base::Entity* entity){
  if(dyn_struct->colorization.color_mode != ope::color::HEATMAP) return;
  //---------------------------

  ImGui::BeginTable("heatmap##mode", 3);

  bool condition = (entity->data.Is.size() == 0);
  if(condition) ImGui::BeginDisabled();
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("I##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INTENSITY)){
    update_color = true;
  }
  if(condition) ImGui::EndDisabled();
  ImGui::SameLine();
  condition = (entity->data.Is_cor.size() == 0);
  if(condition) ImGui::BeginDisabled();
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cor##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INTENSITY_COR)){
    update_color = true;
  }
  if(condition) ImGui::EndDisabled();
  ImGui::SameLine();
  condition = (entity->data.Is_cal.size() == 0);
  if(condition) ImGui::BeginDisabled();
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cal##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INTENSITY_CAL)){
    update_color = true;
  }
  if(condition) ImGui::EndDisabled();

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("H##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::HEIGHT)){
    update_color = true;
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("R##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::RANGE)){
    update_color = true;
  }

  ImGui::EndTable();

  //---------------------------
}
void Colorization::option_intensity(dat::base::Entity* entity){
  int& mode = dyn_struct->colorization.color_mode;
  int& heatmap = dyn_struct->colorization.heatmap_mode;
  //---------------------------

  //Intensity cursor
  if(mode == ope::color::INTENSITY || mode == ope::color::INTENSITY_INV || mode == ope::color::HEATMAP && heatmap == ope::color::heatmap::INTENSITY){
    ImGui::Separator();
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("I diviser", &dyn_struct->operation.intensity.diviser, 1, 10000);
  }

  //---------------------------
}
void Colorization::option_height(dat::base::Entity* entity){
  if(dyn_struct->colorization.heatmap_mode != ope::color::heatmap::HEIGHT) return;
  //---------------------------

  //Height heatmap
  float min = -10;
  float max = 10;
  ImGui::SetNextItemWidth(125);
  ImGui::DragFloatRange2("Z##321", &dyn_struct->colorization.range_height.x, &dyn_struct->colorization.range_height.y, 0.1f, min, max, "%.1f", "%.1f");

  //---------------------------
}

}
