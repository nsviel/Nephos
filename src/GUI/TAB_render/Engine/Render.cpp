#include "Render.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Utility/Node/Namespace.h>
#include <Vulkan/VK_main/VK_imgui.h>
#include <Utility/Element/Window.h>
#include <image/IconsFontAwesome5.h>


namespace gui::engine{

//Constructor / Destructor
Render::Render(GUI* gui){
  //---------------------------

  util::Node* utility = gui->get_utility();
  Engine* engine = gui->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->utl_window = utility->get_utl_window();
  this->gui_control = new gui::engine::Control(gui);
  this->gui_image = new gui::media::Image(gui);
  this->vk_imgui = eng_vulkan->get_vk_imgui();
  this->vk_info = eng_vulkan->get_vk_info();
  this->profiler = new gui::plot::Profiler();

  this->with_profiler_overlay = true;

  //---------------------------
}
Render::~Render(){}

//Main function
void Render::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin("Render", NULL)){
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
void Render::engine_texture(){
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
void Render::engine_overlay(ImVec2 image_pose){
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
