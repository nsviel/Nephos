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
  this->vk_storage = new vk::descriptor::Storage_image(vk_struct);
  this->vk_texture = new vk::texture::Image(vk_struct);

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
  this->update_descriptor(vk_object, *pipeline);
  this->dispatch_pipeline(vk_object, *command_buffer, *pipeline);

  //End command buffer
  vk_command->end_command_buffer(*command_buffer);
  vk_command->submit_command_buffer(command_buffer, vk_struct->core.queue.graphics);

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
/*
  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "depth_raw");
  std::shared_ptr<utl::base::Image> image = std::make_shared<utl::base::Image>("cloud");
  image->format = "RG32";
  image->width = tex_depth->image->width;
  image->height = tex_depth->image->height;
  vk_texture->insert_texture(vk_object, image);

  auto tex_cloud = vk_data->retrieve_vk_texture(vk_object, "cloud");
  vk::memory::Transition vk_transition(vk_struct);
  vk_transition.image_layout_transition(tex_cloud->surface, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);


vk_transition.image_layout_transition(tex_depth->surface, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);


  std::shared_ptr<vk::structure::Texture> tex_table_xy = vk_data->retrieve_vk_texture(vk_object, "depth_table_xy");
vk_transition.image_layout_transition(tex_table_xy->surface, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);



*/
  //---------------------------
}
void Recorder::update_descriptor(vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline){
  //---------------------------

  //Cloud texture
  std::shared_ptr<vk::structure::Storage_image> storage_cloud = vk_storage->query_storage(pipeline.descriptor.descriptor_set, "tex_cloud");
  std::shared_ptr<vk::structure::Texture> tex_cloud = vk_data->retrieve_vk_texture(vk_object, "cloud");
  if(!tex_cloud){
    this->create_texture(vk_object);
    tex_cloud = vk_data->retrieve_vk_texture(vk_object, "cloud");
  }
  vk_storage->actualize_storage(pipeline.descriptor.descriptor_set, *storage_cloud, tex_cloud->surface);

  //Depth texture
  std::shared_ptr<vk::structure::Storage_image> storage_depth = vk_storage->query_storage(pipeline.descriptor.descriptor_set, "tex_depth");
  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "depth_raw");
  vk_storage->actualize_storage(pipeline.descriptor.descriptor_set, *storage_depth, tex_depth->surface);

  //Table XY texture
  std::shared_ptr<vk::structure::Storage_image> storage_tablexy = vk_storage->query_storage(pipeline.descriptor.descriptor_set, "tex_tablexy");
  std::shared_ptr<vk::structure::Texture> tex_table_xy = vk_data->retrieve_vk_texture(vk_object, "depth_table_xy");
  vk_storage->actualize_storage(pipeline.descriptor.descriptor_set, *storage_tablexy, tex_table_xy->surface);



  float* floatData = reinterpret_cast<float*>(tex_table_xy->image->data.data());
  float value = floatData[0];
  //say(value);

  //---------------------------
}
void Recorder::dispatch_pipeline(vk::structure::Object& vk_object, vk::structure::Command_buffer& command_buffer, vk::structure::Pipeline& pipeline){
  //---------------------------

  // Update descriptor set
  vk_pipeline->cmd_bind_descriptor_set(command_buffer.handle, pipeline, pipeline.descriptor.descriptor_set);

  // Dispatch the compute work
  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "depth_raw");
  vk_pipeline->cmd_dispatch_pipeline(command_buffer.handle, *tex_depth->image);

  //---------------------------
}

}
