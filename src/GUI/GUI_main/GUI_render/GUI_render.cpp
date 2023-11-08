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
  this->gui_renderpass = new GUI_renderpass(gui);

  //---------------------------
}
GUI_render::~GUI_render(){}

// Main code
void GUI_render::init(){
  //---------------------------
/*
  gui_renderpass->init_renderpass();
  vk_engine->init();
  dataManager->init();
*/
  //---------------------------
}
void GUI_render::loop(){
  VK_render* vk_render = vk_engine->get_vk_render();
  //---------------------------
/*
  eng_camera->loop_cam_mouse();
  vk_render->loop_draw_frame();
  dataManager->loop();
*/
  //---------------------------
}
void GUI_render::exit(){
  //---------------------------

//  vk_engine->clean();

  //---------------------------
}
