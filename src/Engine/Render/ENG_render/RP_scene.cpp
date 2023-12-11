#include "RP_scene.h"

#include <Engine/Node/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_pipeline/VK_pipeline.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Vulkan/VK_drawing/VK_viewport.h>
#include <Engine/Shader/Scene/SCE_shader.h>
#include <Vulkan/VK_binding/VK_descriptor.h>
#include <Vulkan/VK_binding/VK_uniform.h>
#include <Vulkan/VK_drawing/VK_drawing.h>


//Constructor / Destructor
RP_scene::RP_scene(Engine* engine){
  //---------------------------

  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  vk::structure::Vulkan* struct_vulkan = eng_vulkan->get_struct_vulkan();

  this->eng_shader = engine->get_eng_shader();
  this->vk_engine = eng_vulkan->get_vk_engine();
  this->vk_pipeline = new VK_pipeline(struct_vulkan);
  this->vk_viewport = new VK_viewport(struct_vulkan);
  this->vk_descriptor = new VK_descriptor(struct_vulkan);
  this->vk_uniform = new VK_uniform(struct_vulkan);
  this->vk_drawing = new VK_drawing(struct_vulkan);

  //---------------------------
}
RP_scene::~RP_scene(){}

//Init function
void RP_scene::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "scene";
  renderpass->target = "graphics";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_engine->add_renderpass_description(renderpass);
}
void RP_scene::create_subpass(vk::structure::Renderpass* renderpass){
  SCE_shader* sce_shader = eng_shader->get_sce_shader();
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "shader";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){RP_scene::draw_scene(subpass);};

  vk::structure::Pipeline* pipeline;
  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "line";
  pipeline->definition.topology = "line";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = sce_shader->get_shader_info("Line");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "point";
  pipeline->definition.topology = "point";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = sce_shader->get_shader_info("Point");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("point_size", sizeof(int), 1, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void RP_scene::draw_scene(vk::structure::Subpass* subpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  vk_viewport->cmd_viewport(subpass->command_buffer);
  this->cmd_draw_point(subpass);
  this->cmd_draw_line(subpass);

  //---------------------------
  this->time_renderpass = timer.stop_ms(t1);
}
void RP_scene::cmd_draw_point(vk::structure::Subpass* subpass){
  list<vk::structure::Entity*> list_data = vk_engine->get_list_data();
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("point");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Entity* data =  *next(list_data.begin(), i);

    if(data->object->is_visible && data->object->draw_type_name == "point"){
      vk_uniform->update_uniform("mvp", &data->binding, data->object->mvp);
      vk_uniform->update_uniform("point_size", &data->binding, data->object->draw_point_size);

      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer, pipeline, data->binding.descriptor.set);
      vk_drawing->cmd_draw_data(subpass->command_buffer, data);
    }
  }

  //---------------------------
}
void RP_scene::cmd_draw_line(vk::structure::Subpass* subpass){
  list<vk::structure::Entity*> list_data = vk_engine->get_list_data();
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("line");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Entity* data =  *next(list_data.begin(),i);

    if(data->object->is_visible && data->object->draw_type_name == "line"){
      vk_uniform->update_uniform("mvp", &data->binding, data->object->mvp);

      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer, pipeline, data->binding.descriptor.set);
      vk_drawing->cmd_line_with(subpass->command_buffer, data);
      vk_drawing->cmd_draw_data(subpass->command_buffer, data);
    }
  }

  //---------------------------
}
