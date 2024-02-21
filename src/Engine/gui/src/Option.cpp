#include "Option.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Operation/Namespace.h>


namespace eng::gui{

//Constructor / Destructor
Option::Option(eng::gui::Node* node_gui, bool* show_window){
  //---------------------------

  vk::Node* node_vulkan = node_gui->get_node_vulkan();
  ope::Node* node_operation = node_gui->get_node_operation();

  this->ope_wheel = node_operation->get_ope_wheel();
  this->vk_info = node_vulkan->get_vk_info();

  this->width = 150;
  this->name = "Option";
  this->show_window = show_window;

  //---------------------------
}
Option::~Option(){}

//Main function
void Option::run_panel(){
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
void Option::design_panel(){
  //---------------------------

  this->option_color();
  this->option_wheel();

  //---------------------------
}

//Subfunctions
void Option::option_color(){
  //---------------------------

  //Background color
  vec4* screen_color = vk_info->get_color_background();
  ImGui::SetNextItemWidth(width);
  ImGui::ColorEdit4("Background", (float*)screen_color);

  //---------------------------
  ImGui::Separator();
}
void Option::option_wheel(){
  //---------------------------

  vector<const char*> vec_mode = ope_wheel->get_vec_mode();
  int* mode = ope_wheel->get_mode();
  ImGui::Combo("Wheel mode", mode, vec_mode.data(), vec_mode.size());

  //---------------------------
}

}
