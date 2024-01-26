#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

class VK_surface;
class VK_instance;
class VK_swapchain;
namespace vk::device{class Logical;}
namespace vk::binding{class Descriptor;}
class VK_texture;
namespace vk::data{class Data;}
namespace vk::draw{class Viewport;}
class VK_reload;
class VK_frame;
namespace vk::data{class Canvas;}
class VK_extension;
class VK_pool;
namespace vk::draw{class VK_drawing;}
namespace vk::command{class Synchronization;}
class VK_renderpass;
class FPS_counter;
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}


class VK_engine
{
public:
  //Constructor / Destructor
  VK_engine(vk::structure::Vulkan* struct_vulkan);
  ~VK_engine();

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
  VK_extension* vk_extension;
  VK_surface* vk_surface;
  VK_instance* vk_instance;
  vk::device::Logical* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  vk::binding::Descriptor* vk_descriptor;
  VK_texture* vk_texture;
  VK_pool* vk_pool;
  vk::data::Data* vk_data;
  vk::draw::Viewport* vk_viewport;
  VK_reload* vk_reload;
  vk::command::Synchronization* vk_synchronization;
  VK_frame* vk_frame;
  vk::data::Canvas* vk_canvas;
  vk::draw::VK_drawing* vk_drawing;
  FPS_counter* fps_counter;

  Timer timer;
};
