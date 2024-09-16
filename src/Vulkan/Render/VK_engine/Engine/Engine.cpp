#include "Engine.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Engine::Engine(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pool = new vk::instance::Pool(vk_struct);
  this->vk_extension = new vk::instance::Extension(vk_struct);
  this->vk_instance = new vk::instance::Instance(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_device = new vk::device::Logical(vk_struct);
  this->vk_texture = new vk::image::Texture(vk_struct);
  this->vk_descriptor_set = new vk::binding::Descriptor_set(vk_struct);
  this->vk_data = new vk::data::Data(vk_struct);
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_reload = new vk::shader::Reloader(vk_struct);
  this->vk_frame = new vk::presentation::Frame(vk_struct);
  this->vk_canvas = new vk::data::Canvas(vk_struct);
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_allocator = new vk::command::Allocator(vk_struct);
  this->vk_queue = new vk::queue::Manager(vk_struct);

  //---------------------------
}

}
