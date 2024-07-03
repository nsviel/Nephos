#include "Renderer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Interface/Namespace.h>
#include <Data/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Renderer::Renderer(itf::Node* node_interface){
  //---------------------------

  vk::Node* node_vulkan = node_interface->get_node_vulkan();

  this->itf_navigation = node_interface->get_itf_navigation();
  this->gui_control = node_interface->get_gui_control();
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

  if(ImGui::IsItemHovered()){
    gui_control->run_control();
  }else{
    itf_navigation->disable_camera_view();
  }

  //---------------------------
}

}
