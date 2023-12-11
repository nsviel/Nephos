#include "Render.h"

#include <Node/GUI.h>
#include <Engine/Node/Engine.h>
#include <Vulkan.h>
#include <Utility/Node/Utility.h>
#include <VK_main/VK_imgui.h>
#include <Utility/UTL_window/UTL_window.h>
#include <image/IconsFontAwesome5.h>


namespace gui::engine{

//Constructor / Destructor
Render::Render(GUI* gui){
  //---------------------------

  Utility* utility = gui->get_utility();
  Engine* engine = gui->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->utl_window = utility->get_utl_window();
  this->gui_control = new gui::engine::Control(gui);
  this->gui_image = new gui::media::Image(gui);
  this->vk_imgui = eng_vulkan->get_vk_imgui();

  //---------------------------
}
Render::~Render(){}

//Main function
void Render::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin("Render", NULL)){
    this->engine_window();
    this->engine_control();
    ImGui::End();
  }
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void Render::engine_window(){
  //---------------------------

  ImTextureID texture = vk_imgui->rendered_texture();
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //---------------------------
}
void Render::engine_control(){
  //---------------------------

  if(ImGui::IsItemHovered()){
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 center = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

    gui_control->run_control(center);
  }

  //---------------------------
}

}
