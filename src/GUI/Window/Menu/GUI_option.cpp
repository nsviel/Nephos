#include "GUI_option.h"

#include <GUI.h>
#include <Engine.h>
#include <Param.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>


//Constructor / Destructor
GUI_option::GUI_option(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui = gui;
  Engine* engine = gui->get_engine();
  this->param = engine->get_param();
  this->vk_engine = engine->get_vk_engine();
  this->vk_struct = vk_engine->get_vk_struct();

  this->width = 150;

  //---------------------------
}
GUI_option::~GUI_option(){}

//Main function
void GUI_option::design_panel(){
  //---------------------------

  this->option_font();
  this->option_color();
  this->option_fps();

  //---------------------------
}

//Subfunctions
void GUI_option::option_font(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  ImFont* font_current = ImGui::GetFont();
  if (ImGui::BeginCombo("Font", font_current->GetDebugName())){
    for (ImFont* font : io.Fonts->Fonts){
      ImGui::PushID((void*)font);
      if (ImGui::Selectable(font->GetDebugName(), font == font_current)){
        io.FontDefault = font;
      }
      ImGui::PopID();
    }
    ImGui::EndCombo();
  }

  //---------------------------
  ImGui::Separator();
}
void GUI_option::option_color(){
  if(ImGui::CollapsingHeader("Colors")){
    //---------------------------

    //Background color
    vec4* screen_color = &param->background_color;
    ImGui::SetNextItemWidth(width);
    ImGui::ColorEdit4("Background", (float*)screen_color);

    //---------------------------
    ImGui::Separator();
  }
}
void GUI_option::option_fps(){
  //---------------------------

  //FPS max value
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("FPS max", &param->max_fps, 10, 1000);

  //---------------------------
}
