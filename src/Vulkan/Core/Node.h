#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk::presentation{class Surface;}
namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Frame;}
namespace vk::instance{class Instance;}
namespace vk::instance{class Extension;}
namespace vk::instance{class Pool;}
namespace vk::device{class Logical;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::gui{class Imgui;}
namespace vk::data{class Data;}
namespace vk::data{class Canvas;}
namespace vk::draw{class Viewport;}
namespace vk::shader{class Reloader;}
namespace vk::command{class Allocator;}
namespace vk::command{class Command_buffer;}
namespace vk::command{class Profiler;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::renderpass{class Renderpass;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::queue{class Manager;}
namespace utl::base{class Data;}
namespace utl::base{class Pose;}
namespace vk::draw{class Graphical;}
namespace vk::synchro{class Synchro;}


namespace vk::core{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(vk::Structure* vk_struct);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void clean();

private:
  vk::Structure* vk_struct;
  vk::instance::Extension* vk_extension;
  vk::presentation::Surface* vk_surface;
  vk::instance::Instance* vk_instance;
  vk::device::Logical* vk_device;
  vk::presentation::Swapchain* vk_swapchain;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::command::Command_buffer* vk_command_buffer;
  vk::command::Profiler* vk_profiler;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::instance::Pool* vk_pool;
  vk::data::Data* vk_data;
  vk::draw::Viewport* vk_viewport;
  vk::shader::Reloader* vk_reload;
  vk::presentation::Frame* vk_frame;
  vk::synchro::Synchro* vk_synchro;
  vk::data::Canvas* vk_canvas;
  vk::gui::Imgui* vk_imgui;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
  vk::command::Allocator* vk_allocator;
  vk::queue::Manager* vk_queue;
  vk::draw::Graphical* vk_drawer;
};

}
