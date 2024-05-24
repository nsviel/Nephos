#include "Operation.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Operation::Operation(dyn::Node* node_dynamic){
  //---------------------------

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->ope_operation = new ope::Operation();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::design_operation(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------

  this->draw_ope_button(set);
  this->draw_ope_colorization(set);

  //---------------------------
}

//Subfunction
void Operation::draw_ope_button(dat::base::Set* set){
  //---------------------------

  if(ImGui::TreeNode("Transformation##dynamic")){
    //Centered
    if(ImGui::Button("C##centerentity", ImVec2(20, 0))){
      ope_operation->center_object(set);
    }

    //Rotation 90° around X axis
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##xrotation")){
      ope_operation->make_rotation_X_90d(set, 1);
    }

    ImGui::TreePop();
  }

  //---------------------------
}
void Operation::draw_ope_colorization(dat::base::Set* set){
  //---------------------------

  if(ImGui::TreeNode("Colorization##dynamic")){
    //Colorization mode
    ImGui::RadioButton("RGB##colorization", &dyn_struct->colorization.color_mode, ope::color::CAMERA);
    ImGui::SameLine();
    ImGui::RadioButton("##unicolor", &dyn_struct->colorization.color_mode, ope::color::UNICOLOR);
    ImGui::SameLine();
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
    ImGui::ColorEdit4("##unicolor_choice", (float*)&dyn_struct->colorization.unicolor, flags);
    ImGui::SameLine();
    ImGui::RadioButton("I##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY);
    ImGui::SameLine();
    ImGui::RadioButton("Heatmap##colorization", &dyn_struct->colorization.color_mode, ope::color::HEATMAP);
    ImGui::SameLine();
    ImGui::RadioButton("Structure##colorization", &dyn_struct->colorization.color_mode, ope::color::STRUCTURE);

    //Intensity cursor
    if(dyn_struct->colorization.color_mode == ope::color::INTENSITY){
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Intensity division", &dyn_struct->colorization.intensity_diviser, 1, 5000);
    }

    //Heatmap mode
    if(dyn_struct->colorization.color_mode == ope::color::HEATMAP){
      ImGui::Indent();
      ImGui::RadioButton("I##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INTENSITY);
      ImGui::SameLine();
      ImGui::RadioButton("H##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::HEIGHT);
      ImGui::SameLine();
      ImGui::RadioButton("R##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::RANGE);

      //Intensity heatmap
      if(dyn_struct->colorization.heatmap_mode == ope::color::heatmap::INTENSITY){
        ImGui::SetNextItemWidth(100);
        ImGui::SliderInt("I diviser", &dyn_struct->colorization.intensity_diviser, 1, 5000);
      }

      //Height heatmap
      if(dyn_struct->colorization.heatmap_mode == ope::color::heatmap::HEIGHT){
        float min = -10;
        float max = 10;
        ImGui::SetNextItemWidth(125);
        ImGui::DragFloatRange2("Z##321", &dyn_struct->colorization.range_height.x, &dyn_struct->colorization.range_height.y, 0.1f, min, max, "%.1f", "%.1f");
      }
      ImGui::Unindent();
    }

    ImGui::TreePop();
  }

  //---------------------------
  ImGui::Separator();
}
void Operation::draw_ope_normal(dat::base::Set* set){
  //---------------------------

  if(ImGui::TreeNode("Normal##dynamic")){
    /*//Visibility
    if(ImGui::Checkbox("Visible##2242", &master->operation.normal_visible)){
      //master->visibility_normal();
    }

    //Parameter: kNN
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("kNN", &master->operation.normal_knn, 1, 10);
*/
    ImGui::TreePop();
  }

  //---------------------------
}

}
