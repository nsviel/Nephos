#include "GUI_render.h"
#include "GUI_renderpass.h"

#include <GUI.h>
#include <Engine.h>
#include <Utility.h>
#include <UTL_window/UTL_window.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>


//Constructor / Destructor
GUI_render::GUI_render(GUI* gui){
  //---------------------------

  Utility* utility = gui->get_utility();
  Engine* engine = gui->get_engine();
  UTL_window* utl_window = utility->get_utl_window();

  this->vulkan = engine->get_eng_vulkan();
  //this->vulkan = new Vulkan(utl_window);
  this->vk_engine = vulkan->get_vk_engine();
  this->gui_renderpass = new GUI_renderpass(vulkan);
  this->vk_imgui = vulkan->get_vk_imgui();

  vulkan->set_headless(false);
  vulkan->set_name("GUI_backend");

  //---------------------------
}
GUI_render::~GUI_render(){}

// Main code
void GUI_render::init(){
  //---------------------------

  vk_imgui->init();

  //---------------------------
}
void GUI_render::loop(){
  //---------------------------

  ImGui::Render();

  //---------------------------
}
void GUI_render::clean(){
  //---------------------------

  vk_imgui->clean();

  //---------------------------
}
void GUI_render::wait(){
  //---------------------------

  //vulkan->wait();

  //---------------------------
}
