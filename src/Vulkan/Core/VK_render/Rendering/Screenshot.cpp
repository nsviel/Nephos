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
void Screenshot::render_screenshot(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  this->make_viewport(render);
  this->make_recording(render);

  //---------------------------
}

//Subfunction
void Screenshot::make_viewport(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vk::structure::Viewport viewport;
  viewport.handle.x = 0.0f;
  viewport.handle.y = 0.0f;
  viewport.handle.width = static_cast<float>(render->framebuffer.current->width);
  viewport.handle.height = static_cast<float>(render->framebuffer.current->height);
  viewport.handle.minDepth = 0.0f;
  viewport.handle.maxDepth = 1.0f;

  viewport.scissor.offset = {0, 0};
  viewport.scissor.extent = {
    static_cast<uint32_t>(render->framebuffer.current->width),
    static_cast<uint32_t>(render->framebuffer.current->height)
  };

  //---------------------------
  render->viewport = std::make_shared<vk::structure::Viewport>(viewport);
}
void Screenshot::make_recording(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vk_renderpass->record_renderpass(render);
  vk_struct->core.command.graphics->add_command(render);

  //---------------------------
}

}
