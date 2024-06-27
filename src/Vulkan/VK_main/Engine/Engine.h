#pragma once

#include <GLFW/glfw3.h>
#include <list>

namespace vk::presentation{class Surface;}
namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Frame;}
namespace vk::instance{class Instance;}
namespace vk::instance{class Extension;}
namespace vk::instance{class Pool;}
namespace vk::device{class Logical;}
namespace vk::binding{class Descriptor;}
namespace vk::image{class Texture;}
namespace vk::gui{class Imgui;}
namespace vk::data{class Data;}
namespace vk::data{class Canvas;}
namespace vk::draw{class Viewport;}
namespace vk::shader{class Reloader;}
namespace vk::command{class Allocator;}
namespace vk::command{class Command_buffer;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::renderpass{class Renderpass;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::queue{class Manager;}
namespace utl::base{class Data;}
namespace utl::base{class Pose;}


namespace vk::main{

class Engine
{
public:
  //Constructor / Destructor
  Engine(vk::Structure* vk_struct);
  ~Engine();

public:
  //Main function
  virtual void init(){}
  virtual void loop(){}
  virtual void clean(){}

  //Data function
  void insert_data(utl::base::Data* data, utl::base::Pose* pose);
  void remove_data(utl::base::Data* data);

  //Renderpass function
  void add_renderpass_description(vk::structure::Renderpass* renderpass);
  vk::structure::Renderpass* get_renderpass(int i);
  vk::structure::Object* get_canvas();
  std::list<vk::structure::Object*> get_list_data();
  void set_window(GLFWwindow* window);

protected:
  vk::Structure* vk_struct;
  vk::instance::Extension* vk_extension;
  vk::presentation::Surface* vk_surface;
  vk::instance::Instance* vk_instance;
  vk::device::Logical* vk_device;
  vk::presentation::Swapchain* vk_swapchain;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::command::Command_buffer* vk_command_buffer;
  vk::binding::Descriptor* vk_descriptor;
  vk::image::Texture* vk_texture;
  vk::instance::Pool* vk_pool;
  vk::data::Data* vk_data;
  vk::draw::Viewport* vk_viewport;
  vk::shader::Reloader* vk_reload;
  vk::presentation::Frame* vk_frame;
  vk::data::Canvas* vk_canvas;
  vk::gui::Imgui* vk_imgui;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
  vk::command::Allocator* vk_allocator;
  vk::queue::Manager* vk_queue;
};

}
