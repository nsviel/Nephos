#include "VK_viewport.h"
#include "../VK_engine.h"
#include "../VK_struct.h"

#include <ELE_window/Window.h>
#include <Engine.h>

//Constructor / Destructor
VK_viewport::VK_viewport(VK_engine* vk_engine){
  //---------------------------

  Engine* engine = vk_engine->get_engine();
  this->window = engine->get_window();
  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();

  //---------------------------
}
VK_viewport::~VK_viewport(){}

void VK_viewport::init_viewport(){
  vec2 win_dim = window->get_window_dim();
  //---------------------------

  //Viewport
  viewport = {};
  viewport.x = 0;
  viewport.y = 0;
  viewport.width  = win_dim.x;
  viewport.height = win_dim.y;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  //Full viewport scissor
  scissor = {};
  scissor.offset = {0, 0};
  scissor.extent = vk_struct->window.extent;

  //---------------------------
}
void VK_viewport::update_viewport(){
  vec2 win_dim = window->get_window_dim();
  //---------------------------

  //Viewport scene
  viewport.x = 0;
  viewport.y = 0;
  viewport.width  = win_dim.x;
  viewport.height = win_dim.y;

  //Scissor
  scissor.extent = vk_struct->window.extent;

  //---------------------------
}

Struct_viewport* VK_viewport::create_viewport(){
  vec2 win_dim = window->get_window_dim();
  //---------------------------

  //Viewport
  Struct_viewport* viewport = new Struct_viewport();
  viewport->viewport = {};
  viewport->viewport.x = 0;
  viewport->viewport.y = 0;
  viewport->viewport.width  = win_dim.x;
  viewport->viewport.height = win_dim.y;
  viewport->viewport.minDepth = 0.0f;
  viewport->viewport.maxDepth = 1.0f;

  //Full viewport scissor
  viewport->scissor = {};
  viewport->scissor.offset = {0, 0};
  viewport->scissor.extent = vk_struct->window.extent;

  //---------------------------
  return viewport;
}
