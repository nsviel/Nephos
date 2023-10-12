#include "VK_reload.h"

#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/Pipeline/VK_pipeline.h>


//Constructor / Destructor
VK_reload::VK_reload(VK_engine* vk_engine){
  //---------------------------

  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_pipeline = vk_engine->get_vk_pipeline();

  //---------------------------
}
VK_reload::~VK_reload(){}

//Main function
void VK_reload::hot_shader_reload(string shader_1, string shader_2){
  //---------------------------

say("---PIPELINE RECREATION---");

  Struct_pipeline* pipeline_old = vk_pipeline->get_pipeline_byName(&vk_struct->renderpass_edl, "triangle_EDL");
  Struct_pipeline* pipeline_new = new Struct_pipeline();
  *pipeline_new = *pipeline_old;

  pipeline_new->info.dynamic_state_object.clear();
  vk_pipeline->create_pipeline(&vk_struct->renderpass_edl, pipeline_new);

  vkDeviceWaitIdle(vk_struct->device.device);

  vk_pipeline->clean_pipeline(pipeline_old);
  pipeline_old = pipeline_new;


say("PIPELINE REBUILD !!!!!!!!!!!!");

  //---------------------------
}
