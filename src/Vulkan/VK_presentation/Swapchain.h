#pragma once

#include <Utility/Specific/Common.h>

namespace vk::device{class Physical;}
namespace vk::draw{class Viewport;}
namespace vk::presentation{class Frame;}
namespace vk::renderpass{class Framebuffer;}
namespace vk::presentation{class Surface;}
namespace vk::structure{class Vulkan;}
namespace vk::synchro{class Synchro;}
namespace vk::window{class GLFW;}
namespace vk::gui{class Imgui;}


namespace vk::presentation{

class Swapchain
{
public:
  //Constructor / Destructor
  Swapchain(vk::structure::Vulkan* vk_struct);
  ~Swapchain();

public:
  //Main function
  void init();
  void clean();

  //Swapchain function
  void recreate_swapchain();
  void retrieve_swapchain_image();
  void create_swapchain_handle();
  void find_swapchain_max_nb_image();
  void find_swapchain_surface_format();
  void find_swapchain_presentation_mode();

private:
  vk::structure::Vulkan* vk_struct;
  vk::draw::Viewport* vk_viewport;
  vk::device::Physical* dev_physical;
  vk::presentation::Frame* vk_frame;
  vk::renderpass::Framebuffer* vk_framebuffer;
  vk::presentation::Surface* vk_surface;
  vk::synchro::Synchro* vk_synchro;
  vk::window::GLFW* vk_window;
  vk::gui::Imgui* vk_imgui;
};

}
