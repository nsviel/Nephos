#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Surface;}
namespace vk::window{class Window;}
namespace vk::structure{class Command_set;}
namespace vk::compute{class Pipeline;}
namespace vk::draw{class Renderpass;}
namespace vk::draw{class Graphical;}
namespace vk::synchro{class Semaphore;}
namespace vk::gui{class Imgui;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Semaphore;}
namespace vk::structure{class Command;}
namespace vk::structure{class Render;}


namespace vk::draw{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(vk::Structure* vk_struct);
  ~Renderer();

public:
  //Main function
  void loop();

  //Subfunction
  void make_recording(std::shared_ptr<vk::structure::Render> render);
  void make_submission(std::shared_ptr<vk::structure::Render> render);
  void make_cleaning();

private:
  vk::Structure* vk_struct;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::Window* vk_window;
  vk::draw::Renderpass* vk_renderpass;
  vk::synchro::Semaphore* vk_semaphore;
  vk::draw::Graphical* vk_graphical;
  vk::compute::Pipeline* vk_pipeline;
  vk::gui::Imgui* vk_imgui;
};

}
