#include "GUI_render.h"
#include "GUI_renderpass.h"

#include <GUI.h>
#include <ELE_window/ELE_window.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>

#include <Engine.h>


//Constructor / Destructor
GUI_render::GUI_render(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  this->gui_vulkan = engine->get_eng_vulkan();
  ELE_window* ele_window = gui->get_ele_window();

  this->gui_vulkan = new Vulkan(ele_window);
  this->vk_engine = gui_vulkan->get_vk_engine();
  this->gui_renderpass = new GUI_renderpass(gui_vulkan);

  gui_vulkan->set_headless(false);
  gui_vulkan->set_name("GUI_backend");

  //---------------------------
}
GUI_render::~GUI_render(){}

// Main code
void GUI_render::init(){
  //---------------------------

  gui_renderpass->init_renderpass();
  gui_vulkan->init();

  //---------------------------
}
void GUI_render::loop(){
  //---------------------------

  gui_vulkan->loop();

  //---------------------------
}
void GUI_render::clean(){
  //---------------------------

  gui_vulkan->clean();

  //---------------------------
}
void GUI_render::wait(){
  //---------------------------

  gui_vulkan->wait();

  //---------------------------
}
