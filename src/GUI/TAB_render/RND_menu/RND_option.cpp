#include "RND_option.h"

#include <GUI.h>
#include <Engine.h>
#include <Vulkan.h>
#include <VK_main/VK_info.h>


//Constructor / Destructor
RND_option::RND_option(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->gui = gui;
  this->vk_info = eng_vulkan->get_vk_info();

  this->width = 150;

  //---------------------------
}
RND_option::~RND_option(){}

//Main function
void RND_option::design_panel(){
  //---------------------------

  this->option_color();
  this->option_fps();

  //---------------------------
}

//Subfunctions
void RND_option::option_color(){
  if(ImGui::CollapsingHeader("Colors")){
    //---------------------------

    //Background color
    vec4* screen_color = vk_info->get_color_background();
    ImGui::SetNextItemWidth(width);
    ImGui::ColorEdit4("Background", (float*)screen_color);

    //---------------------------
    ImGui::Separator();
  }
}
void RND_option::option_fps(){
  //---------------------------

  //FPS max value
  int* max_fps = vk_info->get_fps_max();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("FPS max", max_fps, 10, 1000);

  //---------------------------
}
