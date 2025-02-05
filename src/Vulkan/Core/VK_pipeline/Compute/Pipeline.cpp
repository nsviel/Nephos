#include "Pipeline.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline::compute{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_component = new vk::pipeline::compute::Component(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_descriptor = new vk::pipeline::Descriptor(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::init(){
  //---------------------------

  for(auto& [name, pipeline] : vk_struct->core.pipeline.map_compute){
    vk_descriptor->create_pipeline_descriptor(*pipeline);
    vk_component->create_pipeline_component(*pipeline);
  }

  //---------------------------
}
void Pipeline::reset(){
  //---------------------------

  for(auto& [name, pipeline] : vk_struct->core.pipeline.map_compute){
    vk_descriptor->reset_descriptor_set_pool(*pipeline);
  }

  //---------------------------
}
void Pipeline::clean(){
  //---------------------------

  for(auto& [name, pipeline] : vk_struct->core.pipeline.map_compute){
    vk_component->clean_pipeline_component(*pipeline);
    vk_descriptor->clean_pipeline_descriptor(*pipeline);
  }

  //---------------------------
}

//Subfunction
void Pipeline::recreate_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_synchro->wait_idle();
  vk_component->clean_pipeline_component(pipeline);
  vk_component->create_pipeline_component(pipeline);
  vk_synchro->end_idle();

  //---------------------------
}
void Pipeline::cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline.handle);

  //---------------------------
}
void Pipeline::cmd_dispatch_pipeline(VkCommandBuffer& command_buffer, utl::base::Texture& texture){
  //---------------------------

  vkCmdDispatch(command_buffer, texture.width, texture.height, 1);

  //---------------------------
}
void Pipeline::cmd_bind_descriptor_set(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline, vk::structure::Descriptor_set& descriptor_set){
  //---------------------------

  vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline.layout, 0, 1, &descriptor_set.handle, 0, nullptr);

  //---------------------------
}

}
