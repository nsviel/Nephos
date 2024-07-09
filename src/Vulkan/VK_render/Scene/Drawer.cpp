#include "Drawer.h"

#include <Vulkan/Namespace.h>


namespace vk::render::scene{

//Constructor / Destructor
Drawer::Drawer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);

  //---------------------------
}
Drawer::~Drawer(){}

//Main function
void Drawer::draw_scene(vk::structure::Subpass* subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass->command_buffer->handle);
  this->cmd_draw_point(subpass);
  this->cmd_draw_line(subpass);
  this->cmd_draw_triangle(subpass);

  //---------------------------
}

//Subfunction
bool Drawer::check_data(utl::base::Data* data, int typology){
  //---------------------------

  if(data->topology.type != typology) return false;
  if(data->is_visible == false) return false;
  if(data->xyz.size() == 0) return false;
  if(data->rgba.size() == 0) return false;
  if(data->rgba.size() != data->xyz.size()) return false;

  //---------------------------
  return true;
}
void Drawer::cmd_draw_point(vk::structure::Subpass* subpass){
  std::list<vk::structure::Object*>& list_data = vk_struct->data.list_vk_object;
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("point");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->handle, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Object* vk_object =  *next(list_data.begin(), i);
    utl::base::Data* data = vk_object->data;
    utl::base::Pose* pose = vk_object->pose;

    if(check_data(data, utl::topology::POINT)){
      vk_uniform->update_uniform("mvp", &vk_object->binding, pose->mvp);
      vk_uniform->update_uniform("point_size", &vk_object->binding, data->topology.width);
      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->handle, pipeline, vk_object->binding.descriptor.set);
      vk_drawer->cmd_draw_data(subpass->command_buffer->handle, vk_object);
    }
  }

  //---------------------------
}
void Drawer::cmd_draw_line(vk::structure::Subpass* subpass){
  std::list<vk::structure::Object*>& list_data = vk_struct->data.list_vk_object;
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("line");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->handle, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Object* vk_object = *next(list_data.begin(), i);
    utl::base::Data* data = vk_object->data;
    utl::base::Pose* pose = vk_object->pose;

    if(check_data(data, utl::topology::LINE)){
      vk_uniform->update_uniform("mvp", &vk_object->binding, pose->mvp);
      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->handle, pipeline, vk_object->binding.descriptor.set);
      vk_drawer->cmd_line_with(subpass->command_buffer->handle, vk_object);
      vk_drawer->cmd_draw_data(subpass->command_buffer->handle, vk_object);
    }
  }

  //---------------------------
}
void Drawer::cmd_draw_triangle(vk::structure::Subpass* subpass){
  std::list<vk::structure::Object*>& list_data = vk_struct->data.list_vk_object;
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("triangle");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->handle, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Object* vk_object =  *next(list_data.begin(), i);
    utl::base::Data* data = vk_object->data;
    utl::base::Pose* pose = vk_object->pose;

    if(check_data(data, utl::topology::TRIANGLE)){
      vk_uniform->update_uniform("mvp", &vk_object->binding, pose->mvp);
      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->handle, pipeline, vk_object->binding.descriptor.set);
      vk_drawer->cmd_draw_data(subpass->command_buffer->handle, vk_object);
    }
  }

  //---------------------------
}

}
