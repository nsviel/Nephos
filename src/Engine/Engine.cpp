#include "Engine.h"
#include "Param.h"

#include <Data/Data.h>
#include <Vulkan/VK_engine.h>
#include <Camera/Camera.h>
#include <Window/Window.h>
#include <Shader/Shader.h>
#include <GPU/GPU_data.h>
#include <GPU/GPU_texture.h>


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
  this->data = new Data(this);

  //---------------------------
}
Engine::~Engine(){
  //---------------------------

  delete data;

  //---------------------------
}

void Engine::init(){
  //---------------------------

  vk_engine->init_vulkan();
  window->compute_window_dim();
  data->init();

  //---------------------------
}
void Engine::loop(){
  //---------------------------

  //cameraManager->input_cam_mouse();
  vk_engine->draw_frame();

  //---------------------------
}
void Engine::exit(){
  //---------------------------

  //vk_engine->device_wait_idle();
  vk_engine->clean_vulkan();

  //---------------------------
}
void Engine::wait_for_gpu_idle(){
  //---------------------------

  vk_engine->device_wait_idle();

  //---------------------------
}
void Engine::reset(){
  //---------------------------

  cameraManager->reset_camera();
  data->reset();

  //---------------------------
}
