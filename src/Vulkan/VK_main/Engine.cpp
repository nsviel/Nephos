#include "Engine.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Engine::Engine(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pool = new vk::instance::Pool(struct_vulkan);
  this->vk_extension = new vk::instance::Extension(struct_vulkan);
  this->vk_instance = new vk::instance::Instance(struct_vulkan);
  this->vk_viewport = new vk::draw::Viewport(struct_vulkan);
  this->vk_surface = new vk::presentation::Surface(struct_vulkan);
  this->vk_device = new vk::device::Logical(struct_vulkan);
  this->vk_texture = new vk::main::Texture(struct_vulkan);
  this->vk_descriptor = new vk::binding::Descriptor(struct_vulkan);
  this->vk_data = new vk::data::Data(struct_vulkan);
  this->vk_swapchain = new vk::presentation::Swapchain(struct_vulkan);
  this->vk_renderpass = new vk::renderpass::Renderpass(struct_vulkan);
  this->vk_reload = new vk::shader::Reloader(struct_vulkan);
  this->vk_frame = new vk::presentation::Frame(struct_vulkan);
  this->vk_canvas = new vk::data::Canvas(struct_vulkan);
  this->vk_drawing = new vk::draw::Drawer(struct_vulkan);
  this->vk_synchronization = new vk::synchro::Semaphore(struct_vulkan);
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);
  this->vk_imgui = new vk::main::Imgui(struct_vulkan);
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);
  this->vk_semaphore = new vk::synchro::Semaphore(struct_vulkan);

  //---------------------------
}
Engine::~Engine(){}

//Main function
void Engine::init(){
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init();
  vk_surface->init();
  vk_device->init();
  vk_pool->init();
  vk_fence->init();
  vk_semaphore->init_pool();
  vk_command_buffer->init();
  vk_canvas->init();

  //Render
  vk_swapchain->create_swapchain();
  vk_viewport->init();
  vk_renderpass->init();
  vk_imgui->init();
  vk_frame->create_frame();

  //---------------------------
}
void Engine::loop(){
  //---------------------------

  //vk_imgui->render();

  vk_drawing->draw_frame();
  vk_command_buffer->submit();
  vk_command_buffer->reset();
  //vk_imgui->render();
  //vk_imgui->new_frame();

  //---------------------------
}
void Engine::clean(){
  //---------------------------

  vk_synchronization->clean();
  vk_texture->clean();
  vk_renderpass->clean();
  vk_swapchain->clean();
  vk_canvas->clean();
  vk_data->clean();
  vk_command_buffer->clean();
  vk_fence->clean();
  vk_semaphore->clean_pool();
  vk_pool->clean();
  vk_device->clean();
  vk_surface->clean();
  vk_instance->clean();

  //---------------------------
}

//Specific function
void Engine::device_wait_idle(){
  //---------------------------

  VkResult result = vkDeviceWaitIdle(struct_vulkan->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] device wait idle");
  }

  //---------------------------
}
void Engine::reload_shader(string shader, string subshader){
  //---------------------------

  vk_reload->hot_shader_reload(shader, subshader);

  //---------------------------
}

//Data function
void Engine::insert_data_in_engine(utl::type::Data* data, utl::type::Pose* pose){
  if(data == nullptr) return;
  //---------------------------

  //Check if data already in engine
  bool is_in_list = false;
  vk::structure::Object* vk_object;
  for(int i=0; i<struct_vulkan->data.list_vk_object.size(); i++){
    vk_object = *next(struct_vulkan->data.list_vk_object.begin(), i);

    if(data->UID == vk_object->data->UID){
      is_in_list = true;
      break;
    }
  }

  //If not, insert it
  if(is_in_list){
    vk_data->update_data(data, vk_object);
  }else{
    vk_data->insert_data(data, pose);
  }

  //---------------------------
}
void Engine::remove_data_in_engine(utl::type::Data* data){
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<struct_vulkan->data.list_vk_object.size(); i++){
    vk::structure::Object* vk_object = *next(struct_vulkan->data.list_vk_object.begin(),i);
    if(data->UID == vk_object->data->UID){
      vk_data->clean_vk_object(vk_object);
      struct_vulkan->data.list_vk_object.remove(vk_object);
    }
  }

  //---------------------------
}

//Renderpass function
void Engine::add_renderpass_description(vk::structure::Renderpass* renderpass){
  //---------------------------

  struct_vulkan->render.vec_renderpass.push_back(renderpass);

  //---------------------------
}
vk::structure::Renderpass* Engine::get_renderpass(int i){
  //---------------------------

  return struct_vulkan->render.vec_renderpass[i];

  //---------------------------
}
vk::structure::Renderpass* Engine::get_renderpass_presentation(int i){
  //---------------------------

  return struct_vulkan->render.get_renderpass_byName("gui");

  //---------------------------
}
vk::structure::Object* Engine::get_canvas(){
  //---------------------------

  return &struct_vulkan->data.canvas;

  //---------------------------
}
std::list<vk::structure::Object*> Engine::get_list_data(){
  return struct_vulkan->data.list_vk_object;
}
void Engine::set_window(GLFWwindow* window){
  struct_vulkan->window.glfw_window = window;
}

}
