#include "Renderer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Renderer/Namespace.h>
#include <Data/Namespace.h>
#include <Control/Namespace.h>


namespace rnd::gui{

//Constructor / Destructor
Renderer::Renderer(rnd::Node* node_renderer){
  //---------------------------

  vk::Node* node_vulkan = node_renderer->get_node_vulkan();
  ctr::Node* node_control = node_renderer->get_node_control();

  this->ctr_navigation = node_control->get_ctr_navigation();
  this->gui_control = node_control->get_gui_control();
  this->vk_imgui = node_vulkan->get_vk_imgui();
  this->vk_struct = node_vulkan->get_vk_struct();

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

  this->engine_texture();

  //---------------------------
}

//Subfunction
void Renderer::engine_texture(){
  if(vk_struct->param.headless) return;
  //---------------------------

  //Retrieve rendering texture
  ImTextureID texture = vk_imgui->query_engine_texture();
  if(texture == 0) return;

  //Display at window dimension
  ImGui::Image(texture, ImGui::GetContentRegionAvail());

  //Control
  if(ImGui::IsItemHovered()){
    gui_control->run_control();
  }else{
    ctr_navigation->disable_camera_view();
  }

  //---------------------------
}

}
