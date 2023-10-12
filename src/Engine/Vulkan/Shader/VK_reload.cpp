#include "VK_reload.h"

#include <Engine.h>
#include <Shader/Shader.h>
#include <Shader/EDL/EDL_shader.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/Pipeline/VK_pipeline.h>
#include <Vulkan/Renderpass/VK_renderpass.h>
#include <Vulkan/Renderpass/RP_edl.h>


//Constructor / Destructor
VK_reload::VK_reload(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_renderpass = vk_engine->get_vk_renderpass();

  //---------------------------
}
VK_reload::~VK_reload(){}

//Main function
void VK_reload::hot_shader_reload(string shader_1, string shader_2){
  //---------------------------

  if(shader_1 == "EDL"){
    RP_edl* rp_edl = vk_renderpass->get_rp_edl();
    rp_edl->recreate_pipeline_edl();
  }

  //---------------------------
}
