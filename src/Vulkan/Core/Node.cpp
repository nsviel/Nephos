#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::core{

//Constructor / Destructor
Node::Node(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pool = new vk::instance::Pool(vk_struct);
  this->vk_extension = new vk::instance::Extension(vk_struct);
  this->vk_instance = new vk::instance::Instance(vk_struct);
  this->vk_viewport = new vk::presentation::Viewport(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_device = new vk::device::Logical(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_data = new vk::data::Data(vk_struct);
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_reload = new vk::shader::Reloader(vk_struct);
  this->vk_frame = new vk::presentation::Frame(vk_struct);
  this->vk_canvas = new vk::data::Canvas(vk_struct);
  this->vk_command_buffer = new vk::commandbuffer::Pool(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_allocator = new vk::commandbuffer::Allocator(vk_struct);
  this->vk_queue = new vk::command::Queue(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_pipeline = new vk::pipeline::compute::Pipeline(vk_struct);
  this->vk_renderer = new vk::render::Renderer(vk_struct);
  this->vk_texture = new vk::texture::Texture(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
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
  vk_texture->init();

  //Render
  vk_swapchain->init();
  vk_viewport->init();
  vk_renderpass->init();
  vk_imgui->init();
  vk_semaphore->init_pool();
  vk_pipeline->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_renderer->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vk_synchro->wait_idle();
  vk_queue->clean();
  vk_imgui->clean();
  vk_renderpass->clean();
  vk_pipeline->clean();
  vk_swapchain->clean();
  vk_canvas->clean();
  vk_texture->clean();
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
