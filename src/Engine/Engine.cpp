#include "Engine.h"
#include "Param.h"

#include <ENG_data/ENG_data.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <ENG_camera/ENG_camera.h>
#include <ELE_window/Window.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_render/ENG_renderpass.h>


//Constructor / Destructor
Engine::Engine(Window* window){
  //---------------------------

  this->window = window;
  this->param = new Param();
  this->eng_camera = new ENG_camera(this);
  this->eng_shader = new ENG_shader(this);
  this->vk_engine = new VK_engine(window);
  this->dataManager = new ENG_data(this);
  this->eng_renderpass = new ENG_renderpass(this);

  //---------------------------
}
Engine::~Engine(){
  //---------------------------

  delete param;
  delete eng_camera;
  delete eng_shader;
  delete vk_engine;
  delete dataManager;

  //---------------------------
}

void Engine::init(){
  //---------------------------

  eng_renderpass->init_renderpass();
  vk_engine->init();
  dataManager->init();

  //---------------------------
}
void Engine::loop(){
  VK_render* vk_render = vk_engine->get_vk_render();
  //---------------------------

  eng_camera->loop_cam_mouse();
  vk_render->loop_draw_frame();
  dataManager->loop();

  //---------------------------
}
void Engine::exit(){
  //---------------------------

  vk_engine->clean();

  //---------------------------
}
void Engine::wait_for_gpu_idle(){
  //---------------------------

  vk_engine->device_wait_idle();

  //---------------------------
}
void Engine::reset(){
  //---------------------------

  eng_camera->reset();
  dataManager->reset();

  //---------------------------
}
