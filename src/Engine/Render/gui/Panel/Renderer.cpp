#include "Renderer.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::render::gui{

//Constructor / Destructor
Renderer::Renderer(eng::render::Node* node_render){
  //---------------------------

  eng::Engine* engine = node_render->get_engine();
  utl::Node* node_utility = engine->get_node_utility();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->utl_window = node_utility->get_utl_window();
  this->ope_control = new eng::ope::gui::Control(engine);
  this->node_camera = engine->get_node_camera();
  this->vk_imgui = eng_vulkan->get_vk_imgui();
  this->vk_info = eng_vulkan->get_vk_info();
  this->profiler = new utl::gui::plot::Profiler();

  this->with_profiler_overlay = true;
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
  this->engine_overlay(image_pose);

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
    ope_control->run_control();
    node_camera->gui();
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
