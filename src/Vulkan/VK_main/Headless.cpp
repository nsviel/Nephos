#include "Headless.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Headless::Headless(vk::structure::Vulkan* vk_struct) : vk::main::Engine(vk_struct){
  //---------------------------


  //---------------------------
}
Headless::~Headless(){}

//Main function
void Headless::init(){
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init();
  vk_device->init();
  vk_allocator->init();
  vk_queue->init();
  vk_pool->init();
  vk_fence->init_pool();
  vk_canvas->init();

  //Render
  vk_viewport->init();
  vk_renderpass->init();
  vk_imgui->init();
  vk_semaphore->init_pool();

  //---------------------------
}
void Headless::loop(){
  //---------------------------

  vk_drawing->draw_frame();
  vk_semaphore->reset_pool();

  //---------------------------
}
void Headless::clean(){
  //---------------------------

  vk_texture->clean();
  vk_renderpass->clean();
  vk_swapchain->clean();
  vk_canvas->clean();
  vk_data->clean();
  vk_fence->clean_pool();
  vk_semaphore->clean_pool();
  vk_allocator->clean();
  vk_pool->clean();
  vk_device->clean();
  vk_surface->clean();
  vk_instance->clean();

  //---------------------------
}

}
