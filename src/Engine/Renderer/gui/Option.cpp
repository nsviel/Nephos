#include "Option.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Operation/Namespace.h>
#include <Renderer/Namespace.h>
#include <Control/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Option::Option(itf::Node* node_interface, bool* show_window){
  //---------------------------

  eng::Node* node_engine = node_interface->get_node_engine();
  vk::Node* node_vulkan = node_interface->get_node_vulkan();
  dat::Node* node_data = node_engine->get_node_data();

  //this->ctl_struct = node_interface->get_ctl_struct();
  //this->ctl_wheel = node_interface->get_ctl_wheel();
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

  //std::vector<const char*> vec_mode = ctl_wheel->get_vec_mode();
  //ImGui::Combo("Wheel mode", &ctl_struct->wheel_mode, vec_mode.data(), vec_mode.size());

  //---------------------------
}
void Option::visualization_mode(){
  //---------------------------

  bool truc = true;
  ImGui::Checkbox("Visualization mode", &truc);

  //---------------------------
}

}
