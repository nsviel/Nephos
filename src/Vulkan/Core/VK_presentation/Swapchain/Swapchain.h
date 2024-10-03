#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::device{class Physical;}
namespace vk::draw{class Viewport;}
namespace vk::presentation{class Frame;}
namespace vk::renderpass{class Framebuffer;}
namespace vk::presentation{class Surface;}
namespace vk::structure{class Semaphore;}
namespace vk::synchro{class Synchro;}
namespace vk::window{class Window;}
namespace vk::window{class Event;}
namespace vk::gui{class Imgui;}
namespace vk::synchro{class Semaphore;}
namespace vk::renderpass{class Renderpass;}


namespace vk::presentation{

class Swapchain
{
public:
  //Constructor / Destructor
  Swapchain(vk::Structure* vk_struct);
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
  bool acquire_next_image(vk::structure::Semaphore& semaphore);

private:
  vk::Structure* vk_struct;
  vk::draw::Viewport* vk_viewport;
  vk::device::Physical* dev_physical;
  vk::presentation::Frame* vk_frame;
  vk::renderpass::Framebuffer* vk_framebuffer;
  vk::presentation::Surface* vk_surface;
  vk::synchro::Synchro* vk_synchro;
  vk::window::Window* vk_window;
  vk::window::Event* vk_event;
  vk::gui::Imgui* vk_imgui;
  vk::synchro::Semaphore* vk_semaphore;
  vk::renderpass::Renderpass* vk_renderpass;
};

}
