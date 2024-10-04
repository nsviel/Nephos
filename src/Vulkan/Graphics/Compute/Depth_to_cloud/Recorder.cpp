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
  this->vk_data = new vk::data::Retriever(vk_struct);
  this->vk_command = new vk::command::Command(vk_struct);
  this->vk_commandbuffer = new vk::commandbuffer::Command_buffer(vk_struct);
  this->vk_allocator = new vk::commandbuffer::Allocator(vk_struct);
  this->vk_storage = new vk::descriptor::Storage_image(vk_struct);
  this->vk_tex_storage = new vk::texture::Storage(vk_struct);
  this->vk_descriptor = new vk::pipeline::Descriptor(vk_struct);

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::run_compute(vk::structure::Object& vk_object){
  std::shared_ptr<vk::structure::Pipeline> pipeline = vk_struct->core.pipeline.map_compute["depth_to_cloud"];
  //---------------------------

  auto descriptor_set = vk_descriptor->query_descriptor_set(*pipeline);

  //Start command buffer
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_commandbuffer->query_graphics_command_buffer("depth_to_cloud");
  vk_commandbuffer->start_command_buffer_primary(*command_buffer);

  this->bind_pipeline(*command_buffer, *pipeline);
  this->update_descriptor(vk_object, *descriptor_set);
  this->dispatch_pipeline(vk_object, *command_buffer, *pipeline, *descriptor_set);

  //End command buffer
  vk_commandbuffer->end_command_buffer(*command_buffer);
  vk_command->submit_graphics_command(command_buffer);

  //---------------------------
}

//Subfunction
void Recorder::bind_pipeline(vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(command_buffer.handle, pipeline);

  //---------------------------
}
void Recorder::create_texture(vk::structure::Object& vk_object){
  //---------------------------

  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "depth_raw");
  std::shared_ptr<utl::base::Storage> storage = std::make_shared<utl::base::Storage>("cloud");
  storage->format = "RGBA32";
  storage->width = tex_depth->depth->width;
  storage->height = tex_depth->depth->height;
  vk_tex_storage->insert_storage_empty(*vk_object.data, storage);

  //---------------------------
}
void Recorder::update_descriptor(vk::structure::Object& vk_object, vk::structure::Descriptor_set& descriptor_set){
  //---------------------------

  //Cloud texture
  std::shared_ptr<vk::structure::Storage_image> storage_cloud = vk_storage->query_storage(descriptor_set, "tex_cloud");
  std::shared_ptr<vk::structure::Texture> tex_cloud = vk_data->retrieve_vk_texture(vk_object, "cloud");
  if(!tex_cloud){
    this->create_texture(vk_object);
    tex_cloud = vk_data->retrieve_vk_texture(vk_object, "cloud");
  }
  vk_storage->actualize_storage(descriptor_set, *storage_cloud, tex_cloud->surface);

  //Depth texture
  std::shared_ptr<vk::structure::Storage_image> storage_depth = vk_storage->query_storage(descriptor_set, "tex_depth");
  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "depth_raw");
  vk_storage->actualize_storage(descriptor_set, *storage_depth, tex_depth->surface);

  //Table XY texture
  std::shared_ptr<vk::structure::Storage_image> storage_tablexy = vk_storage->query_storage(descriptor_set, "tex_tablexy");
  std::shared_ptr<vk::structure::Texture> tex_table_xy = vk_data->retrieve_vk_texture(vk_object, "depth_table_xy");
  vk_storage->actualize_storage(descriptor_set, *storage_tablexy, tex_table_xy->surface);




  //---------------------------
}
void Recorder::dispatch_pipeline(vk::structure::Object& vk_object, vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline, vk::structure::Descriptor_set& descriptor_set){
  //---------------------------

  // Update descriptor set
  vk_pipeline->cmd_bind_descriptor_set(command_buffer.handle, pipeline, descriptor_set);

  // Dispatch the compute work
  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "depth_raw");
  vk_pipeline->cmd_dispatch_pipeline(command_buffer.handle, *tex_depth->depth);

  //---------------------------
}

}
