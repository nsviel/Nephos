#include "Render.h"

#include <Node/GUI.h>
#include <Engine.h>
#include <Utility.h>
#include <UTL_window/UTL_window.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>


namespace gui{

//Constructor / Destructor
Render::Render(GUI* gui){
  //---------------------------

  Utility* utility = gui->get_utility();
  Engine* engine = gui->get_engine();
  UTL_window* utl_window = utility->get_utl_window();

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
