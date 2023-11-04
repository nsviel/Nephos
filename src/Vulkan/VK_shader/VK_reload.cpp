#include "VK_reload.h"

#include <Engine.h>
#include <ENG_shader/Shader.h>
#include <ENG_shader/EDL/EDL_shader.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_renderpass/VK_renderpass.h>
#include <VK_renderpass/RP_edl.h>


//Constructor / Destructor
VK_reload::VK_reload(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_pipeline = new VK_pipeline(vk_engine);
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
