#include "Recorder.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::compute::dtc{

//Constructor / Destructor
Recorder::Recorder(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_pipeline = new vk::compute::Pipeline(vk_struct);

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::run_compute(vk::structure::Object& vk_object, vk::structure::Command_buffer& command_buffer){
  std::shared_ptr<vk::structure::Pipeline> pipeline = vk_struct->core.pipeline.map_compute["depth_to_cloud"];
  //---------------------------

  this->bind_pipeline(vk_object, *pipeline);
  this->update_sampler(*pipeline);

  //---------------------------
}

//Subfunction
void Recorder::bind_pipeline(vk::structure::Object& vk_object, vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(command_buffer->handle, pipeline);





  //---------------------------
}
void Recorder::update_sampler(vk::structure::Pipeline& pipeline){
  //---------------------------



  //---------------------------
}
void Recorder::dispatch_pipeline(vk::structure::Object& vk_object, vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  // Update descriptor set
  vk_descriptor_set->bind_descriptor_set(command_buffer->handle, pipeline, pipeline.descriptor.descriptor_set);

  // Dispatch the compute work
  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "depth_raw");
  vk_pipeline->cmd_dispatch_pipeline(command_buffer->handle, tex_depth->image);

  //---------------------------
}

}
