#include "Engine.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Engine::Engine(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pool = new vk::instance::Pool(vk_struct);
  this->vk_extension = new vk::instance::Extension(vk_struct);
  this->vk_instance = new vk::instance::Instance(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_device = new vk::device::Logical(vk_struct);
  this->vk_texture = new vk::main::Texture(vk_struct);
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_data = new vk::data::Data(vk_struct);
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_reload = new vk::shader::Reloader(vk_struct);
  this->vk_frame = new vk::presentation::Frame(vk_struct);
  this->vk_canvas = new vk::data::Canvas(vk_struct);
  this->vk_drawing = new vk::draw::Graphical(vk_struct);
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_imgui = new vk::main::Imgui(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_allocator = new vk::command::Allocator(vk_struct);
  this->vk_queue = new vk::queue::Manager(vk_struct);

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
  for(int i=0; i<vk_struct->data.list_vk_object.size(); i++){
    vk_object = *next(vk_struct->data.list_vk_object.begin(), i);

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
  std::list<vk::structure::Object*>& list_vk_object = vk_struct->data.list_vk_object;
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

  vk_struct->render.vec_renderpass.push_back(renderpass);

  //---------------------------
}
vk::structure::Renderpass* Engine::get_renderpass(int i){
  //---------------------------

  return vk_struct->render.vec_renderpass[i];

  //---------------------------
}
vk::structure::Renderpass* Engine::get_renderpass_presentation(int i){
  //---------------------------

  return vk_struct->render.get_renderpass_byName("gui");

  //---------------------------
}
vk::structure::Object* Engine::get_canvas(){
  //---------------------------

  return &vk_struct->data.canvas;

  //---------------------------
}
std::list<vk::structure::Object*> Engine::get_list_data(){
  return vk_struct->data.list_vk_object;
}
void Engine::set_window(GLFWwindow* window){
  vk_struct->window.glfw_window = window;
}

}
