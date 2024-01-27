#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace vk::presentation{class VK_surface;}
namespace vk::instance{class Instance;}
namespace vk::presentation{class VK_swapchain;}
namespace vk::device{class Logical;}
namespace vk::binding{class Descriptor;}
namespace vk::main{class Texture;}
namespace vk::data{class Data;}
namespace vk::draw{class Viewport;}
class VK_reload;
namespace vk::presentation{class VK_frame;}
namespace vk::data{class Canvas;}
namespace vk::instance{class Extension;}
namespace vk::instance{class Pool;}
namespace vk::draw{class Drawer;}
namespace vk::command{class Synchronization;}
class VK_renderpass;
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace utl::fps{class Counter;}


namespace vk::main{

class Engine
{
public:
  //Constructor / Destructor
  Engine(vk::structure::Vulkan* struct_vulkan);
  ~Engine();

public:
  //Init function
  void init();
  void init_engine_presentation();
  void init_engine_headless();

  //Main functions
  void loop();
  void clean();

  //Specific function
  void device_wait_idle();
  void reload_shader(string shader, string subshader);

  //Data function
  void insert_data_in_engine(utl::type::Data* data, utl::type::Pose* pose);
  void remove_data_in_engine(utl::type::Data* data);

  //Renderpass function
  void add_renderpass_description(vk::structure::Renderpass* renderpass);
  vk::structure::Renderpass* get_renderpass(int i);
  vk::structure::Renderpass* get_renderpass_presentation(int i);
  vk::structure::Object* get_canvas();
  std::list<vk::structure::Object*> get_list_data();
  void set_window(GLFWwindow* window);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::instance::Extension* vk_extension;
  vk::presentation::VK_surface* vk_surface;
  vk::instance::Instance* vk_instance;
  vk::device::Logical* vk_device;
  vk::presentation::VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  vk::binding::Descriptor* vk_descriptor;
  vk::main::Texture* vk_texture;
  vk::instance::Pool* vk_pool;
  vk::data::Data* vk_data;
  vk::draw::Viewport* vk_viewport;
  VK_reload* vk_reload;
  vk::command::Synchronization* vk_synchronization;
  vk::presentation::VK_frame* vk_frame;
  vk::data::Canvas* vk_canvas;
  vk::draw::Drawer* vk_drawing;
  utl::fps::Counter* fps_counter;

  Timer timer;
};

}
