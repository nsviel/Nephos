#include "Graphical.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Graphical::Graphical(vk::structure::Vulkan* vk_struct) : vk::main::Engine(vk_struct){
  //---------------------------

  //this->vk_window = new vk::window::GLFW(vk_struct);
  this->vk_drawer = new vk::draw::Graphical(vk_struct);

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
  vk_frame->create_swapchain_frame();

  //---------------------------
}
void Graphical::loop(){
  //---------------------------

  vk_drawer->draw_frame();
  vk_semaphore->reset_pool();

  //---------------------------
}
void Graphical::clean(){
  //---------------------------

  vk_queue->clean();
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
