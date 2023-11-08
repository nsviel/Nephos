#include "GUI_render.h"
#include "GUI_renderpass.h"

#include <GUI.h>
#include <ELE_window/ELE_window.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>


//Constructor / Destructor
GUI_render::GUI_render(GUI* gui){
  //---------------------------

  ELE_window* ele_window = gui->get_ele_window();

  this->vk_engine = new VK_engine(ele_window);
  this->vk_render = vk_engine->get_vk_render();
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

  //vk_render->loop_draw_frame();

  //---------------------------
}
void GUI_render::clean(){
  //---------------------------

  vk_engine->clean();

  //---------------------------
}
