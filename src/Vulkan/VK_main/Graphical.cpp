#include "Graphical.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Graphical::Graphical(vk::structure::Vulkan* struct_vulkan) : vk::main::Engine(struct_vulkan){
  //---------------------------


  //---------------------------
}
Graphical::~Graphical(){}

//Main function
void Graphical::init(){
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init();
  vk_surface->init();
  vk_device->init();
  vk_allocator->init();
  vk_queue->init();
  vk_pool->init();
  vk_fence->init_pool();
  vk_canvas->init();

  //Render
  vk_swapchain->create_swapchain();
  vk_viewport->init();
  vk_renderpass->init();
  vk_imgui->init();
  vk_semaphore->init_pool();
  vk_frame->create_frame();

  //---------------------------
}
void Graphical::loop(){
  //---------------------------

  vk_drawing->draw_frame();
  vk_semaphore->reset_pool();

  //---------------------------
}
void Graphical::clean(){
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
