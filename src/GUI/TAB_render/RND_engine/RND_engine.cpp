#include "RND_engine.h"
#include "RND_control.h"

#include <Engine.h>
#include <GUI.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>
#include <VK_struct/struct_vulkan.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
RND_engine::RND_engine(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  VK_engine* vk_engine = engine->get_vk_engine();
  this->vk_imgui = vk_engine->get_vk_imgui();
  this->gui_control = new RND_control(gui);

  //---------------------------
}
RND_engine::~RND_engine(){}

//Main function
void RND_engine::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin("Engine", NULL)){
    this->engine_window();
    this->engine_control();
    ImGui::End();
  }
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void RND_engine::engine_window(){
  //---------------------------

  ImTextureID texture = vk_imgui->engine_texture();
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //---------------------------
}
void RND_engine::engine_control(){
  //---------------------------

  if(ImGui::IsItemHovered()){
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 center = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

    gui_control->run_control(center);
  }

  //---------------------------
}
