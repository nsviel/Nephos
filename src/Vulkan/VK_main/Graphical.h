#pragma once

#include <Vulkan/VK_main/Engine.h>
#include <Utility/Specific/Common.h>

namespace vk::presentation{class Surface;}
namespace vk::instance{class Instance;}
namespace vk::presentation{class Swapchain;}
namespace vk::device{class Logical;}
namespace vk::binding{class Descriptor;}
namespace vk::main{class Texture;}
namespace vk::command{class Allocator;}
namespace vk::main{class Imgui;}
namespace vk::data{class Data;}
namespace vk::draw{class Viewport;}
namespace vk::shader{class Reloader;}
namespace vk::presentation{class Frame;}
namespace vk::data{class Canvas;}
namespace vk::instance{class Extension;}
namespace vk::instance{class Pool;}
namespace vk::draw{class Graphical;}
namespace vk::command{class Command_buffer;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::renderpass{class Renderpass;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::queue{class Manager;}


namespace vk::main{

class Graphical : public vk::main::Engine
{
public:
  //Constructor / Destructor
  Graphical(vk::structure::Vulkan* struct_vulkan);
  ~Graphical();

public:
  //Main functions
  void init();
  void loop();
  void clean();
};

}
