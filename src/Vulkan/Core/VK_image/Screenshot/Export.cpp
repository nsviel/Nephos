#include "Export.h"

#include <Vulkan/Namespace.h>


namespace vk::screenshot{

//Constructor / Destructor
Export::Export(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_format = new vk::screenshot::Format(vk_struct);

  //---------------------------
}
Export::~Export(){}

//Main function
void Export::make_screenshot_color(){
  //---------------------------

  vk::structure::Renderpass& renderpass = *vk_struct->graphics.render.renderpass.postprocess;
  vk_format->export_image_to_bmp(renderpass.framebuffer.color);

  //---------------------------
}
void Export::make_screenshot_depth(){
  //---------------------------

  vk::structure::Renderpass& renderpass = *vk_struct->graphics.render.renderpass.geometry;
  vk_format->export_depth_to_bmp(renderpass.framebuffer.depth);

  //---------------------------
}

}
