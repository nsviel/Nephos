#include "Engine.h"
#include "Param.h"

#include <ENG_data/Data.h>
#include <Vulkan/VK_engine.h>
#include <ENG_camera/Camera.h>
#include <ELE_window/Window.h>
#include <ENG_shader/Shader.h>
#include <ENG_gpu/GPU_data.h>
#include <ENG_gpu/GPU_texture.h>


//Constructor / Destructor
Engine::Engine(Window* window){
  //---------------------------

  this->window = window;
  this->param = new Param();
  this->cameraManager = new Camera(this);
  this->shaderManager = new Shader(this);
  this->vk_engine = new VK_engine(this);
  this->gpu_data = new GPU_data(vk_engine);
  this->gpu_texture = new GPU_texture(vk_engine);
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
  delete gpu_texture;
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
  //---------------------------

  cameraManager->loop_cam_mouse();
  vk_engine->loop_draw_frame();

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
