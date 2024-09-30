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
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_data = new vk::data::Function(vk_struct);
  this->vk_command = new vk::command::Command(vk_struct);
  this->vk_command_allocator = new vk::command::Allocator(vk_struct);

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::run_compute(vk::structure::Object& vk_object){
  std::shared_ptr<vk::structure::Pipeline> pipeline = vk_struct->core.pipeline.map_compute["depth_to_cloud"];
  //---------------------------

  //Start command buffer
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  vk_command->start_command_buffer_primary(*command_buffer);

  this->bind_pipeline(*command_buffer, *pipeline);
  this->update_descriptor(*pipeline);
  this->dispatch_pipeline(vk_object, *command_buffer, *pipeline);

  //End command buffer
  vk_command->end_command_buffer(*command_buffer);
  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->command_buffer = command_buffer;
  vk_struct->core.queue.graphics->add_command(std::move(command));

  //---------------------------
}

//Subfunction
void Recorder::bind_pipeline(vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(command_buffer.handle, pipeline);

  //---------------------------
}
void Recorder::update_descriptor(vk::structure::Pipeline& pipeline){
  //---------------------------



  //---------------------------
}
void Recorder::dispatch_pipeline(vk::structure::Object& vk_object, vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  // Update descriptor set
  vk_descriptor_set->bind_descriptor_set(command_buffer.handle, pipeline, pipeline.descriptor.descriptor_set);

  // Dispatch the compute work
  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "depth_raw");
  vk_pipeline->cmd_dispatch_pipeline(command_buffer.handle, *tex_depth->image);

  //---------------------------
}

}
