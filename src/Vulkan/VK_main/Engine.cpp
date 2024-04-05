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
  this->vk_drawing = new vk::draw::Graphical(struct_vulkan);
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);
  this->vk_imgui = new vk::main::Imgui(struct_vulkan);
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);
  this->vk_semaphore = new vk::synchro::Semaphore(struct_vulkan);
  this->vk_allocator = new vk::command::Allocator(struct_vulkan);
  this->vk_queue = new vk::queue::Manager(struct_vulkan);

  //---------------------------
}
Engine::~Engine(){}

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
      vk_data->update_data(data, vk_object);
      return;
    }
  }

  //If not, insert it
  vk_data->insert_data(data, pose);

  //---------------------------
}
void Engine::remove_data_in_engine(utl::type::Data* data){
  std::list<vk::structure::Object*>& list_vk_object = struct_vulkan->data.list_vk_object;
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<list_vk_object.size(); i++){
    vk::structure::Object* vk_object = *next(list_vk_object.begin(),i);

    if(data->UID == vk_object->data->UID){
      list_vk_object.remove(vk_object);
      vk_data->clean_vk_object(vk_object);
    }
  }

  //---------------------------
}

//Renderpass function
void Engine::reload_shader(string shader, string subshader){
  //---------------------------

  vk_reload->hot_shader_reload(shader, subshader);

  //---------------------------
}
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
