#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Structure;}
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
namespace vk::presentation{class Viewport;}
namespace vk::shader{class Reloader;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::commandbuffer{class Pool;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::renderpass{class Renderpass;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::command{class Queue;}
namespace utl::base{class Data;}
namespace utl::base{class Pose;}
namespace vk::render{class Renderer;}
namespace vk::synchro{class Synchro;}
namespace vk::pipeline::compute{class Pipeline;}


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
  vk::commandbuffer::Pool* vk_command_buffer;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::instance::Pool* vk_pool;
  vk::data::Data* vk_data;
  vk::presentation::Viewport* vk_viewport;
  vk::shader::Reloader* vk_reload;
  vk::pipeline::compute::Pipeline* vk_pipeline;
  vk::presentation::Frame* vk_frame;
  vk::synchro::Synchro* vk_synchro;
  vk::data::Canvas* vk_canvas;
  vk::gui::Imgui* vk_imgui;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
  vk::commandbuffer::Allocator* vk_allocator;
  vk::command::Queue* vk_queue;
  vk::render::Renderer* vk_renderer;
};

}
