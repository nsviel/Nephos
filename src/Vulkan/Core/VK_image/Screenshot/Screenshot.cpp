#include "Screenshot.h"

#include <Vulkan/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Screenshot::Screenshot(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_export = new vk::image::Export(vk_struct);

  //---------------------------
}
Screenshot::~Screenshot(){}

//Main function
void Screenshot::make_screenshot_color(){
  //---------------------------

  vk::structure::Renderpass& renderpass = *vk_struct->graphics.render.renderpass.postprocess;
  vk_export->export_image_to_bmp(renderpass.framebuffer.color);

  //---------------------------
}
void Screenshot::make_screenshot_depth(){
  //---------------------------

  vk::structure::Renderpass& renderpass = *vk_struct->graphics.render.renderpass.geometry;
  vk_export->export_depth_to_bmp(renderpass.framebuffer.depth);

  //---------------------------
}

}
