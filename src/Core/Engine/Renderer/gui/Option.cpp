#include "Option.h"

#include <Core/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <Renderer/Namespace.h>
#include <Engine/Control/Namespace.h>


namespace rnd::gui{

//Constructor / Destructor
Option::Option(rnd::Node* node_renderer, bool* show_window){
  //---------------------------

  core::Node* node_core = node_renderer->get_node_core();
  vk::Node* node_vulkan = node_renderer->get_node_vulkan();
  dat::Node* node_data = node_core->get_node_data();

  //this->ctr_struct = node_renderer->get_ctr_struct();
  //this->ctr_wheel = node_renderer->get_ctr_wheel();
  this->vk_interface = node_vulkan->get_vk_interface();

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
  this->visualization_mode();

  //---------------------------
}

//Subfunctions
void Option::option_color(){
  //---------------------------

  //Background color
  glm::vec4* screen_color = vk_interface->get_color_background();
  ImGui::SetNextItemWidth(width);
  ImGui::ColorEdit4("Background", (float*)screen_color);

  //---------------------------
  ImGui::Separator();
}
void Option::option_wheel(){
  //---------------------------

  //std::vector<const char*> vec_mode = ctr_wheel->get_vec_mode();
  //ImGui::Combo("Wheel mode", &ctr_struct->wheel_mode, vec_mode.data(), vec_mode.size());

  //---------------------------
}
void Option::visualization_mode(){
  //---------------------------

  bool truc = true;
  ImGui::Checkbox("Visualization mode", &truc);

  //---------------------------
}

}
