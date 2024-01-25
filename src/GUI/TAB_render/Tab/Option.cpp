#include "Option.h"

#include <GUI.h>
#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_info.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Option::Option(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  eng::Engine* engine = gui->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->gui = gui;
  this->vk_info = eng_vulkan->get_vk_info();

  this->width = 150;

  //---------------------------
}
Option::~Option(){}

//Main function
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
