#include "Pipeline.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_component = new vk::pipeline::Component(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::create_pipeline(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      vk_component->create_pipeline_object(renderpass, *pipeline);
    }
  }

  //---------------------------
}
void Pipeline::clean_pipeline(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      vk_component->clean_pipeline_object(*pipeline);
    }
  }

  //---------------------------
}
void Pipeline::recreate_pipeline(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_synchro->wait_idle_and_pause();
  vk_component->clean_pipeline_object(pipeline);
  vk_component->create_pipeline_object(renderpass, pipeline);
  vk_synchro->end_idle();

  //---------------------------
}

//Subfunction
void Pipeline::add_pipeline_topology(vk::structure::Subpass& subpass, std::shared_ptr<vk::structure::Pipeline> pipeline){
  //---------------------------

  //Subset pipeline map
  subpass.map_pipeline[pipeline->info.name] = pipeline;

  //Whole program pipeline map
  vk_struct->core.pipeline.map[pipeline->info.topology] = pipeline;

  //---------------------------
}
void Pipeline::cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.handle);

  //---------------------------
}

}
