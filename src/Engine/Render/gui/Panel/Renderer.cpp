#include "Renderer.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::render::gui{

//Constructor / Destructor
Renderer::Renderer(eng::render::Node* node_render){
  //---------------------------

  eng::Node* node_engine = node_render->get_node_engine();
  utl::Node* node_utility = node_engine->get_node_utility();
  vk::Node* eng_vulkan = node_engine->get_eng_vulkan();

  this->utl_window = node_utility->get_utl_window();
  this->node_operation = node_engine->get_node_operation();
  this->node_camera = node_engine->get_node_camera();
  this->vk_imgui = eng_vulkan->get_vk_imgui();
  this->vk_info = eng_vulkan->get_vk_info();

  this->name = "Renderer";

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::run_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin(name.c_str(), NULL)){
    this->design_panel();
    ImGui::End();
  }
  ImGui::PopStyleVar();

  //---------------------------
}
void Renderer::design_panel(){
  //---------------------------

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  this->engine_texture();

  //---------------------------
}

//Subfunction
void Renderer::engine_texture(){
  //---------------------------

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  ImTextureID texture = vk_imgui->query_engine_texture();
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});
  if(ImGui::IsItemHovered()){
    node_operation->control();
    node_camera->control();
  }

  //---------------------------
}

}
