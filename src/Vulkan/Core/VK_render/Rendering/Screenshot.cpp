#include "Screenshot.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Screenshot::Screenshot(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_renderpass = new vk::draw::Renderpass(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_swapchain = new vk::draw::Swapchain(vk_struct);
  this->vk_pipeline = new vk::pipeline::compute::Pipeline(vk_struct);

  //---------------------------
}
Screenshot::~Screenshot(){}

//Main function
void Screenshot::make_screenshot(){
  std::shared_ptr<vk::structure::Render> render = std::make_shared<vk::structure::Render>();
  //---------------------------

  auto& renderpass = vk_struct->core.drawer.vec_renderpass[0];
  render->renderpass = renderpass;
  render->framebuffer = std::make_shared<vk::structure::Framebuffer>(renderpass->framebuffer.screenshot);


  vk::structure::Viewport viewport;
  viewport.handle.x = 0.0f;
  viewport.handle.y = 0.0f;
  viewport.handle.width = static_cast<float>(render->framebuffer->width);
  viewport.handle.height = static_cast<float>(render->framebuffer->height);
  viewport.handle.minDepth = 0.0f;
  viewport.handle.maxDepth = 1.0f;

  viewport.scissor.offset = {0, 0};
  viewport.scissor.extent = {
    static_cast<uint32_t>(render->framebuffer->width),
    static_cast<uint32_t>(render->framebuffer->height)
  };


  render->viewport = std::make_shared<vk::structure::Viewport>(viewport);

  vk_renderpass->record_renderpass(render);

  vk_struct->core.command.graphics->add_command(render);

  vk::screenshot::Export vk_screenshot(vk_struct);
  vk_screenshot.make_screenshot_color();

  //---------------------------
}

}
