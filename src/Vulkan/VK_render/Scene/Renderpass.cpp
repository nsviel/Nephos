#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::scene{

//Constructor / Destructor
Renderpass::Renderpass(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_engine = new vk::main::Engine(vk_struct);
  this->vk_pipeline = new vk::renderpass::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);
  this->shader_scene = new vk::render::scene::Shader(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Init function
void Renderpass::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "scene";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_engine->add_renderpass_description(renderpass);
}
void Renderpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "shader";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Renderpass::draw_scene(subpass);};

  //Line pipeline
  vk::structure::Pipeline* pipeline;
  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "line";
  pipeline->definition.topology = "line";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = shader_scene->get_shader_info("Line");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //Point pipeline
  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "point";
  pipeline->definition.topology = "point";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = shader_scene->get_shader_info("Point");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("point_size", sizeof(int), 1, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //Triangle pipeline
  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.topology = "triangle";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = shader_scene->get_shader_info("Triangle");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void Renderpass::draw_scene(vk::structure::Subpass* subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass->command_buffer->handle);
  this->cmd_draw_point(subpass);
  this->cmd_draw_line(subpass);
  this->cmd_draw_triangle(subpass);

  //---------------------------
}
void Renderpass::cmd_draw_point(vk::structure::Subpass* subpass){
  list<vk::structure::Object*> list_data = vk_engine->get_list_data();
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
void Renderpass::cmd_draw_line(vk::structure::Subpass* subpass){
  list<vk::structure::Object*> list_data = vk_engine->get_list_data();
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
void Renderpass::cmd_draw_triangle(vk::structure::Subpass* subpass){
  list<vk::structure::Object*> list_data = vk_engine->get_list_data();
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

//Subfunction
bool Renderpass::check_data(utl::base::Data* data, int topology){
  bool data_ok = false;
  //---------------------------

  bool is_visible = data->is_visible;
  bool has_topology = data->topology.type == topology;
  bool has_xyz = data->xyz.size() != 0;
  bool has_rgb = data->rgba.size() != 0;
  bool same_length = data->rgba.size() == data->xyz.size();

  if(is_visible && has_topology && has_xyz && has_rgb && same_length){
    data_ok = true;
  }

  //---------------------------
  return data_ok;
}

}
