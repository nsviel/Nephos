#include "Screenshot.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Screenshot::Screenshot(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_renderpass = new vk::render::Renderpass(vk_struct);

  //---------------------------
}
Screenshot::~Screenshot(){}

//Main function
void Screenshot::make_screenshot(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  this->make_viewport(render);
  this->make_recording(render);
  this->make_export();

  //---------------------------
}

//Subfunction
void Screenshot::make_viewport(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

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

  //---------------------------
  render->viewport = std::make_shared<vk::structure::Viewport>(viewport);
}
void Screenshot::make_recording(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  auto& renderpass = vk_struct->core.drawer.vec_renderpass[0];

  vk_renderpass->record_renderpass(render);
  vk_struct->core.command.graphics->add_command(render);

  //---------------------------
}
void Screenshot::make_export(){
  //---------------------------

  vk::screenshot::Export vk_screenshot(vk_struct);
  vk_screenshot.make_screenshot_color();

  //---------------------------
}

}
