#include "Render.h"

#include <Node/GUI.h>
#include <Engine/Node/Engine.h>
#include <Utility/Node/Namespace.h>
#include <Utility/Element/Window.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Vulkan/VK_main/VK_imgui.h>


namespace gui{

//Constructor / Destructor
Render::Render(GUI* gui){
  //---------------------------

  utility::Node* utility = gui->get_utility();
  Engine* engine = gui->get_engine();
  util::element::Window* utl_window = utility->get_utl_window();

  this->vulkan = engine->get_eng_vulkan();
  //this->vulkan = new Vulkan(utl_window);
  this->vk_engine = vulkan->get_vk_engine();
  this->gui_renderpass = new gui::Renderpass(vulkan);
  this->vk_imgui = vulkan->get_vk_imgui();

  vulkan->set_headless(false);
  vulkan->set_name("GUI_backend");

  //---------------------------
}
Render::~Render(){}

// Main code
void Render::init(){
  //---------------------------

  vk_imgui->init();

  //---------------------------
}
void Render::loop(){
  //---------------------------

  ImGui::Render();

  //---------------------------
}
void Render::clean(){
  //---------------------------

  vk_imgui->clean();

  //---------------------------
}
void Render::new_frame(){
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  //---------------------------
}

}
