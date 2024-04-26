#include "Renderer.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Camera/Namespace.h>
#include <Operation/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Rendering/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace rnd::gui{

//Constructor / Destructor
Renderer::Renderer(rnd::Node* node_rendering){
  //---------------------------

  eng::Node* node_engine = node_rendering->get_node_engine();
  vk::Node* node_vulkan = node_rendering->get_node_vulkan();
  engine::cam::Node* node_camera = node_engine->get_node_camera();

  this->node_operation = node_engine->get_node_operation();
  this->cam_control = node_camera->get_gui_control();
  this->vk_imgui = node_vulkan->get_vk_imgui();
  this->vk_interface = node_vulkan->get_vk_interface();
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
    vec2 panel_center = vec2(center_x, center_y);


    node_operation->control();
    cam_control->run_control(panel_center);
  }else{
    cam_control->disable_camera_view();
  }

  //---------------------------
}

}
