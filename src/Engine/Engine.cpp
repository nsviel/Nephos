#include "Engine.h"
#include "Param.h"

#include <ENG_data/Data.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <ENG_camera/Camera.h>
#include <ELE_window/Window.h>
#include <ENG_shader/Shader.h>
#include <VK_main/GPU_data.h>


//Constructor / Destructor
Engine::Engine(Window* window){
  //---------------------------

  this->window = window;
  this->param = new Param();
  this->cameraManager = new Camera(this);
  this->shaderManager = new Shader(this);
  this->vk_engine = new VK_engine(this);
  this->gpu_data = new GPU_data(vk_engine);
  this->dataManager = new Data(this);

  //---------------------------
}
Engine::~Engine(){
  //---------------------------

  delete param;
  delete cameraManager;
  delete shaderManager;
  delete vk_engine;
  delete gpu_data;
  delete dataManager;

  //---------------------------
}

void Engine::init(){
  //---------------------------

  vk_engine->init();
  dataManager->init();

  //---------------------------
}
void Engine::loop(){
  VK_render* vk_render = vk_engine->get_vk_render();
  //---------------------------

  cameraManager->loop_cam_mouse();
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

  cameraManager->reset();
  dataManager->reset();

  //---------------------------
}
