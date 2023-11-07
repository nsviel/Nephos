#include "VK_reload.h"

#include <Engine.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_shader/EDL/EDL_shader.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_renderpass/VK_renderpass.h>


//Constructor / Destructor
VK_reload::VK_reload(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_renderpass = new VK_renderpass(vk_engine);

  //---------------------------
}
VK_reload::~VK_reload(){}

//Main function
void VK_reload::hot_shader_reload(string shader_1, string shader_2){
  //---------------------------

  if(shader_1 == "Scene"){
    Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(struct_vulkan->vec_renderpass[0], "point");
    this->recreate_pipeline(struct_vulkan->vec_renderpass[0], pipeline);
  }
  if(shader_1 == "EDL"){
    Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(struct_vulkan->vec_renderpass[1], "triangle_EDL");
    this->recreate_pipeline(struct_vulkan->vec_renderpass[1], pipeline);
  }

  //---------------------------
}
void VK_reload::recreate_pipeline(Struct_renderpass* renderpass, Struct_pipeline* pipeline){
  //---------------------------

  vkDeviceWaitIdle(struct_vulkan->device.device);
  vk_pipeline->clean_pipeline(pipeline);
  vk_pipeline->create_pipeline(renderpass, pipeline);

  //---------------------------
}
