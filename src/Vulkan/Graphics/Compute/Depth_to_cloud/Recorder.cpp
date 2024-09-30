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
void Recorder::run_compute(){
  std::shared_ptr<vk::structure::Pipeline> pipeline = vk_struct->core.pipeline.map_compute["depth_to_cloud"];
  //---------------------------

  this->bind_pipeline(*pipeline);
  this->update_sampler(*pipeline);

  //---------------------------
}

//Subfunction
void Recorder::bind_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, pipeline);

  //---------------------------
}
void Recorder::update_sampler(vk::structure::Pipeline& pipeline){
  //---------------------------



  //---------------------------
}

}
