#pragma once

#include <Utility/Specific/common.h>

namespace vk::presentation{class Surface;}
namespace vk::instance{class Instance;}
namespace vk::presentation{class Swapchain;}
namespace vk::device{class Logical;}
namespace vk::binding{class Descriptor;}
namespace vk::main{class Texture;}
namespace vk::main{class Imgui;}
namespace vk::data{class Data;}
namespace vk::draw{class Viewport;}
namespace vk::shader{class Reloader;}
namespace vk::presentation{class Frame;}
namespace vk::data{class Canvas;}
namespace vk::instance{class Extension;}
namespace vk::instance{class Pool;}
namespace vk::draw{class Drawer;}
namespace vk::synchro{class Synchronization;}
namespace vk::command{class Command_buffer;}
namespace vk::renderpass{class Renderpass;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}


namespace vk::main{

class Headless
{
public:
  //Constructor / Destructor
  Headless(vk::structure::Vulkan* struct_vulkan);
  ~Headless();

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
  void insert_data_in_engine_test(utl::type::Data* data, utl::type::Pose* pose);
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
  vk::presentation::Surface* vk_surface;
  vk::instance::Instance* vk_instance;
  vk::device::Logical* vk_device;
  vk::presentation::Swapchain* vk_swapchain;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::command::Command_buffer* vk_command_buffer;
  vk::binding::Descriptor* vk_descriptor;
  vk::main::Texture* vk_texture;
  vk::instance::Pool* vk_pool;
  vk::data::Data* vk_data;
  vk::draw::Viewport* vk_viewport;
  vk::shader::Reloader* vk_reload;
  vk::synchro::Synchronization* vk_synchronization;
  vk::presentation::Frame* vk_frame;
  vk::data::Canvas* vk_canvas;
  vk::draw::Drawer* vk_drawing;
  vk::main::Imgui* vk_imgui;
};

}
