#include "VK_engine.h"

#include <Vulkan/Namespace.h>
#include <Utility/Function/Timer/fct_timer.h>
#include <Utility/Function/Timer/FPS_counter.h>


//Constructor / Destructor
VK_engine::VK_engine(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pool = new VK_pool(struct_vulkan);
  this->vk_extension = new VK_extension(struct_vulkan);
  this->vk_instance = new VK_instance(struct_vulkan);
  this->vk_viewport = new vk::draw::VK_viewport(struct_vulkan);
  this->vk_surface = new VK_surface(struct_vulkan);
  this->vk_device = new vk::device::Logical(struct_vulkan);
  this->vk_texture = new VK_texture(struct_vulkan);
  this->vk_descriptor = new vk::binding::Descriptor(struct_vulkan);
  this->vk_data = new vk::data::Data(struct_vulkan);
  this->vk_swapchain = new VK_swapchain(struct_vulkan);
  this->vk_renderpass = new VK_renderpass(struct_vulkan);
  this->vk_reload = new VK_reload(struct_vulkan);
  this->vk_frame = new VK_frame(struct_vulkan);
  this->vk_canvas = new vk::data::Canvas(struct_vulkan);
  this->vk_drawing = new vk::draw::VK_drawing(struct_vulkan);
  this->vk_synchronization = new vk::command::Synchronization(struct_vulkan);
  this->fps_counter = new FPS_counter();

  //---------------------------
}
VK_engine::~VK_engine(){}

//Init function
void VK_engine::init(){
  timer_time t1 = timer.start_t();
  //---------------------------

  if(struct_vulkan->param.headless){
    this->init_engine_headless();
  }else{
    this->init_engine_presentation();
  }

  //---------------------------
  struct_vulkan->profiler.engine_init = timer.stop_us(t1) / 1000;
}
void VK_engine::init_engine_presentation(){
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init();
  vk_surface->init();
  vk_device->init();
  vk_pool->init();
  vk_canvas->init();

  //Render
  vk_swapchain->create_swapchain();
  vk_viewport->init();
  vk_renderpass->init();
  vk_frame->create_frame();

  //---------------------------
}
void VK_engine::init_engine_headless(){
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init();
  vk_device->init();
  vk_pool->init();
  vk_canvas->init();
  vk_synchronization->init();

  //Render
  vk_viewport->init();
  vk_renderpass->init();

  //---------------------------
}

//Main function
void VK_engine::loop(){
  struct_vulkan->profiler.time_ref = std::chrono::system_clock::now();
  struct_vulkan->profiler.vec_task.clear();
  //---------------------------

  vk_drawing->draw_frame();

  //---------------------------
  struct_vulkan->profiler.engine_fps = fps_counter->update();
}
void VK_engine::clean(){
  //---------------------------

  vk_synchronization->clean();
  vk_texture->clean();
  vk_renderpass->clean();
  vk_swapchain->clean();
  vk_canvas->clean();
  vk_data->clean();
  vk_pool->clean();
  vk_device->clean();
  vk_surface->clean();
  vk_instance->clean();

  //---------------------------
}

//Specific function
void VK_engine::device_wait_idle(){
  //---------------------------

  VkResult result = vkDeviceWaitIdle(struct_vulkan->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] device wait idle");
  }

  //---------------------------
}
void VK_engine::reload_shader(string shader, string subshader){
  //---------------------------

  vk_reload->hot_shader_reload(shader, subshader);

  //---------------------------
}

//Data function
void VK_engine::insert_data_in_engine(utl::type::Data* data, utl::type::Pose* pose){
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
void VK_engine::remove_data_in_engine(utl::type::Data* data){
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
void VK_engine::add_renderpass_description(vk::structure::Renderpass* renderpass){
  //---------------------------

  struct_vulkan->render.vec_renderpass.push_back(renderpass);

  //---------------------------
}
vk::structure::Renderpass* VK_engine::get_renderpass(int i){
  //---------------------------

  return struct_vulkan->render.vec_renderpass[i];

  //---------------------------
}
vk::structure::Renderpass* VK_engine::get_renderpass_presentation(int i){
  //---------------------------

  return struct_vulkan->render.get_renderpass_byName("gui");

  //---------------------------
}
vk::structure::Object* VK_engine::get_canvas(){
  //---------------------------

  return &struct_vulkan->data.canvas;

  //---------------------------
}
std::list<vk::structure::Object*> VK_engine::get_list_data(){
  return struct_vulkan->data.list_vk_object;
}
void VK_engine::set_window(GLFWwindow* window){
  struct_vulkan->window.glfw_window = window;
}
