#include "Renderer.h"

#include <Vulkan/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace vk::render::gui{

//Constructor / Destructor
Renderer::Renderer(vk::Node* node_vulkan){
  //---------------------------

  //this->node_operation = node_engine->get_node_operation();
  //this->node_camera = node_engine->get_node_camera();
  this->vk_imgui = node_vulkan->get_vk_imgui();
  this->vk_info = node_vulkan->get_vk_info();

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
  ImTextureID texture = vk_imgui->rendered_texture();
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});
  if(ImGui::IsItemHovered()){
    //node_operation->control();
    //node_camera->control();
  }

  //---------------------------
}

}
