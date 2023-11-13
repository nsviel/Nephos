#include "RND_engine.h"
#include "RND_control.h"
#include <ELE_window/ELE_window.h>
#include <GUI.h>
#include <image/IconsFontAwesome5.h>
#include <RES_gpu/GUI_image.h>

#include <Engine.h>
#include <Vulkan.h>
#include <VK_main/VK_imgui.h>

//Constructor / Destructor
RND_engine::RND_engine(GUI* gui){
  //---------------------------

  this->ele_window = gui->get_ele_window();
  this->gui_control = new RND_control(gui);
  this->gui_image = new GUI_image(gui);

  Engine* engine = gui->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  this->vk_imgui = eng_vulkan->get_vk_imgui();

  //---------------------------
}
RND_engine::~RND_engine(){}

//Main function
void RND_engine::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin("Engine", NULL)){
    this->engine_window();
    this->engine_control();
    ImGui::End();
  }
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void RND_engine::engine_window(){
  //---------------------------

  Struct_image* image = vk_imgui->rendered_image();

  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  ImTextureID texture = reinterpret_cast<ImTextureID>(descriptor);

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //---------------------------
}
void RND_engine::engine_control(){
  //---------------------------

  if(ImGui::IsItemHovered()){
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 center = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

    gui_control->run_control(center);
  }

  //---------------------------
}
