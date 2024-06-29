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

  this->itf_camera = node_interface->get_itf_camera();
  this->gui_edition = node_interface->get_gui_edition();
  this->gui_navigation = node_interface->get_gui_navigation();
  this->itf_player = node_interface->get_gui_player();

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

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  this->engine_texture();

  //---------------------------
}

//Subfunction
void Renderer::engine_texture(){
  if(vk_struct->param.headless) return;
  //---------------------------

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  ImTextureID texture = vk_imgui->query_engine_texture();
  if(texture == 0) return;
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});
  if(ImGui::IsItemHovered()){

    //Get center of the current panel
    ImVec2 panel_pose = ImGui::GetWindowPos();
    ImVec2 panel_size = ImGui::GetWindowSize();
    int center_x = panel_pose.x + panel_size.x * 0.5f;
    int center_y = panel_pose.y + panel_size.y * 0.5f;
    glm::vec2 panel_center = glm::vec2(center_x, center_y);

    itf_player->run_control();
    gui_edition->run_control();
    gui_navigation->run_control(panel_center);
  }else{
    itf_camera->disable_camera_view();
  }

  //---------------------------
}

}
