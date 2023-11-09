#include "GUI_render.h"
#include "GUI_renderpass.h"

#include <GUI.h>
#include <ELE_window/ELE_window.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>


//Constructor / Destructor
GUI_render::GUI_render(GUI* gui){
  //---------------------------

  ELE_window* ele_window = gui->get_ele_window();

  this->gui_vulkan = new Vulkan(ele_window);
  this->vk_engine = gui_vulkan->get_vk_engine();
  this->vk_render = gui_vulkan->get_vk_render();
  this->gui_renderpass = new GUI_renderpass(vk_engine);

  //---------------------------
}
GUI_render::~GUI_render(){}

// Main code
void GUI_render::init(){
  //---------------------------

  gui_renderpass->init_renderpass();
  vk_engine->init();

  //---------------------------
}
void GUI_render::loop(){
  //---------------------------

  gui_vulkan->loop();

  //---------------------------
}
void GUI_render::clean(){
  //---------------------------

  vk_engine->clean();

  //---------------------------
}
void GUI_render::wait(){
  //---------------------------

  vk_engine->device_wait_idle();

  //---------------------------
}
