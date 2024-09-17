#include "Pipeline.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_descriptor = new vk::pipeline::Descriptor(vk_struct);
  this->vk_shader = new vk::pipeline::Shader(vk_struct);
  this->vk_vertex = new vk::pipeline::Vertex(vk_struct);
  this->vk_component = new vk::pipeline::Component(vk_struct);
  this->vk_layout = new vk::pipeline::Layout(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::create_pipeline(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      this->create_pipeline_struct(renderpass, *pipeline);
    }
  }

  //---------------------------
}
void Pipeline::clean_pipeline(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      this->clean_pipeline_struct(*pipeline);
    }
  }

  //---------------------------
}
void Pipeline::recreate_pipeline(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_synchro->wait_idle_and_pause();
  this->clean_pipeline_struct(pipeline);
  this->create_pipeline_struct(renderpass, pipeline);
  vk_synchro->end_idle();

  //---------------------------
}
void Pipeline::add_pipeline_topology(vk::structure::Subpass& subpass, std::shared_ptr<vk::structure::Pipeline> pipeline){
  //---------------------------

  //Subset pipeline map
  subpass.map_pipeline[pipeline->info.name] = pipeline;

  //Whole program pipeline map
  vk_struct->core.pipeline.map[pipeline->info.topology] = pipeline;

  //---------------------------
}

//Subfunction
void Pipeline::create_pipeline_struct(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_descriptor->create_pipeline_descriptor(pipeline);
  vk_shader->create_pipeline_shader(pipeline);
  vk_vertex->pipeline_vertex_description(pipeline);
  vk_layout->create_pipeline_layout(pipeline);
  vk_component->create_pipeline_object(renderpass, pipeline);
  vk_shader->clean_pipeline_shader(pipeline);

  //---------------------------
}
void Pipeline::clean_pipeline_struct(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_component->clean_pipeline_handle(pipeline);
  vk_layout->clean_pipeline_layout(pipeline);
  vk_descriptor->clean_pipeline_descriptor(pipeline);

  //---------------------------
}
void Pipeline::cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.handle);

  //---------------------------
}

}
