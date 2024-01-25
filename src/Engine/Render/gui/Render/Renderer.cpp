#include "Renderer.h"

#include <Engine/Engine.h>
#include <Engine/Render/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_imgui.h>
#include <Vulkan/VK_main/VK_info.h>
#include <Utility/Namespace.h>
#include <Utility/Element/src/Namespace.h>
#include <Utility/GUI/Plot/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::render::gui{

//Constructor / Destructor
Renderer::Renderer(Engine* engine){
  //---------------------------

  utl::Node* utility = engine->get_node_utility();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->utl_window = utility->get_utl_window();
  this->ope_control = new eng::ope::gui::Control(engine);
  this->cam_node = engine->get_node_camera();
  this->vk_imgui = eng_vulkan->get_vk_imgui();
  this->vk_info = eng_vulkan->get_vk_info();
  this->profiler = new utl::gui::plot::Profiler();

  this->with_profiler_overlay = true;

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin("Renderer", NULL)){
    ImVec2 image_pose = ImGui::GetCursorScreenPos();
    this->engine_texture();
    this->engine_control();
    this->engine_overlay(image_pose);
    ImGui::End();
  }
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void Renderer::engine_texture(){
  //---------------------------

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  ImTextureID texture = vk_imgui->rendered_texture();
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //---------------------------
}
void Renderer::engine_control(){
  //---------------------------

  if(ImGui::IsItemHovered()){
    ope_control->run_control();
    cam_node->gui();
  }

  //---------------------------
}
void Renderer::engine_overlay(ImVec2 image_pose){
  if(!with_profiler_overlay) return;
  //---------------------------

  profiler->reset();
  vector<vk::structure::Task>& vec_gpu_task = vk_info->get_profiler_data();
  for(int i=0; i<vec_gpu_task.size(); i++){
    vk::structure::Task task = vec_gpu_task[i];
    profiler->add_task(task.time_beg, task.time_end, task.name);
  }

  profiler->loop(image_pose);

  //---------------------------
}

}
