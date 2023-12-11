#include "VK_reload.h"

#include <VK_struct/Namespace.h>
#include <VK_pipeline/VK_pipeline.h>


//Constructor / Destructor
VK_reload::VK_reload(vk::structure::Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pipeline = new VK_pipeline(struct_vulkan);

  //---------------------------
}
VK_reload::~VK_reload(){}

//Main function
void VK_reload::hot_shader_reload(string shader_1, string shader_2){
  //---------------------------

  if(shader_1 == "Scene"){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("scene");
    if(renderpass == nullptr) return;
    vk::structure::Subpass* subpass = renderpass->vec_subpass[0];
    vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("point");
    this->recreate_pipeline(renderpass, pipeline);
  }
  if(shader_1 == "EDL"){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("edl");
    if(renderpass == nullptr) return;
    vk::structure::Subpass* subpass = renderpass->vec_subpass[0];
    vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("triangle_EDL");
    this->recreate_pipeline(renderpass, pipeline);
  }

  //---------------------------
}
void VK_reload::recreate_pipeline(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline){
  //---------------------------

  vkDeviceWaitIdle(struct_vulkan->device.device);
  vk_pipeline->clean_pipeline_struct(pipeline);
  vk_pipeline->create_pipeline_struct(renderpass, pipeline);

  //---------------------------
}
