#include "Renderer.h"

#include <Engine/Renderer/Namespace.h>
#include <Engine/Control/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace rnd::gui{

//Constructor / Destructor
Renderer::Renderer(rnd::Node* node_renderer){
  //---------------------------

  vk::Node* node_vulkan = node_renderer->get_node_vulkan();
  ctr::Node* node_control = node_renderer->get_node_control();

  this->ctr_navigation = node_control->get_ctr_navigation();
  this->gui_control = node_control->get_gui_control();
  this->vk_data = node_vulkan->get_vk_data();
  this->vk_struct = node_vulkan->get_vk_struct();

  this->name = "Renderer";

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::run_panel(){
  //---------------------------

  ImGuiWindowFlags flag = ImGuiWindowFlags_NoCollapse;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin(name.c_str(), NULL, flag)){
    this->design_panel();
    ImGui::End();
  }
  ImGui::PopStyleVar();

  //---------------------------
}
void Renderer::design_panel(){
  //---------------------------

  this->engine_texture();

  //---------------------------
}

//Subfunction
void Renderer::engine_texture(){
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  //Draw render texture
  ImVec2 dim = ImGui::GetContentRegionAvail();
  vk_data->draw_render_texture(glm::vec2(dim.x, dim.y));

  //Control
  if(ImGui::IsItemHovered()){
    gui_control->run_control();
  }else{
    ctr_navigation->disable_camera_view();
  }

  //---------------------------
}

}
