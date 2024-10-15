#include "Pipeline.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_component = new vk::render::Component(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_descriptor = new vk::pipeline::Descriptor(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::create_pipeline(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      vk_descriptor->create_pipeline_descriptor(*pipeline);
      vk_component->create_pipeline_component(renderpass, *pipeline);
    }
  }

  //---------------------------
}
void Pipeline::clean_pipeline(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      vk_component->clean_pipeline_component(*pipeline);
      vk_descriptor->clean_pipeline_descriptor(*pipeline);
    }
  }

  //---------------------------
}
void Pipeline::recreate_pipeline(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_synchro->wait_idle();
  vk_component->clean_pipeline_component(pipeline);
  vk_component->create_pipeline_component(renderpass, pipeline);
  vk_synchro->end_idle();

  //---------------------------
}

//Subfunction
void Pipeline::add_pipeline_topology(vk::structure::Subpass& subpass, std::shared_ptr<vk::structure::Pipeline> pipeline){
  //---------------------------

  //Subset pipeline map
  subpass.map_pipeline[pipeline->info.name] = pipeline;

  //Whole program pipeline map
  vk_struct->core.pipeline.map_topology[pipeline->info.topology] = pipeline;

  //---------------------------
}
void Pipeline::cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_descriptor->reset_descriptor_set_pool(pipeline);
  vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.handle);

  //---------------------------
}
void Pipeline::cmd_bind_descriptor_set(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline, vk::structure::Descriptor_set& descriptor_set){
  //---------------------------

  vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 1, &descriptor_set.handle, 0, nullptr);

  //---------------------------
}

}
