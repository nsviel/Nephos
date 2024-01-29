#include "Option.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::gui{

//Constructor / Destructor
Option::Option(eng::Node* node_engine, bool* show_window){
  //---------------------------

  vk::Node* eng_vulkan = node_engine->get_eng_vulkan();

  this->vk_info = eng_vulkan->get_vk_info();

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

  this->option_fps();
  ImGui::Separator();
  this->option_color();

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
}
void Option::option_fps(){
  //---------------------------

  //FPS max value
  int* max_fps = vk_info->get_fps_max();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("FPS max", max_fps, 10, 1000);

  //---------------------------
}

}
