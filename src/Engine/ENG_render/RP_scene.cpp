#include "RP_scene.h"

#include <Engine.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_drawing/VK_viewport.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_shader/Scene/SCE_shader.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>
#include <VK_data/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_binding/VK_uniform.h>
#include <VK_drawing/VK_drawing.h>


//Constructor / Destructor
RP_scene::RP_scene(Engine* engine){
  //---------------------------

  this->eng_shader = engine->get_eng_shader();
  this->vk_engine = engine->get_vk_engine();
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_viewport = new VK_viewport(vk_engine);
  this->vk_command = new VK_command(vk_engine);
  this->vk_descriptor = new VK_descriptor(vk_engine);
  this->vk_uniform = new VK_uniform(vk_engine);
  this->vk_drawing = new VK_drawing(vk_engine);

  //---------------------------
}
RP_scene::~RP_scene(){}

//Init function
Struct_renderpass* RP_scene::init_renderpass(){
  //---------------------------

  //Renderpass
  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "scene";
  renderpass->subpass_trg = "shader";
  renderpass->draw_task = [this](Struct_renderpass* renderpass){RP_scene::draw_scene(renderpass);};

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  return renderpass;
}
void RP_scene::create_subpass(Struct_renderpass* renderpass){
  SCE_shader* sce_shader = eng_shader->get_sce_shader();
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  renderpass->vec_subpass.push_back(subpass);
  Struct_pipeline* pipeline;

  pipeline = new Struct_pipeline();
  pipeline->definition.name = "line";
  pipeline->definition.topology = "line";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = sce_shader->get_shader_info("Line");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  subpass->vec_pipeline.push_back(pipeline);

  pipeline = new Struct_pipeline();
  pipeline->definition.name = "point";
  pipeline->definition.topology = "point";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = sce_shader->get_shader_info("Point");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("point_size", sizeof(int), 1, TYPE_UNIFORM, STAGE_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}

//Draw function
void RP_scene::draw_scene(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  Struct_framebuffer* framebuffer = renderpass->framebuffer;
  vk_command->start_render_pass(renderpass, framebuffer->fbo, false);
  vk_viewport->cmd_viewport(renderpass);
  this->cmd_draw_scene(renderpass);
  this->cmd_draw_glyph(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
  this->time_renderpass = timer.stop_ms(t1);
}
void RP_scene::cmd_draw_scene(Struct_renderpass* renderpass){
  list<Struct_data*> list_data_scene = vk_engine->get_list_data_scene();
  //---------------------------

  Struct_subpass* subpass = renderpass->vec_subpass[0];
  Struct_pipeline* pipeline = subpass->get_pipeline_byName("point");
  vk_pipeline->cmd_bind_pipeline(renderpass, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);

    if(data->object->draw_type_name == "point" && data->object->is_visible){
      vk_uniform->update_uniform("mvp", &data->binding, data->object->mvp);
      vk_uniform->update_uniform("point_size", &data->binding, data->object->draw_point_size);

      vk_descriptor->cmd_bind_descriptor(renderpass, "point", data->binding.descriptor.set);
      vk_drawing->cmd_draw_data(renderpass, data);
    }
  }

  //---------------------------
}
void RP_scene::cmd_draw_glyph(Struct_renderpass* renderpass){
  list<Struct_data*> list_data_glyph = vk_engine->get_list_data_glyph();
  //---------------------------

  Struct_subpass* subpass = renderpass->vec_subpass[0];
  Struct_pipeline* pipeline = subpass->get_pipeline_byName("line");
  vk_pipeline->cmd_bind_pipeline(renderpass, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data =  *next(list_data_glyph.begin(),i);

    if(data->object->draw_type_name == "line" && data->object->is_visible){
      vk_uniform->update_uniform("mvp", &data->binding, data->object->mvp);

      vk_descriptor->cmd_bind_descriptor(renderpass, "line", data->binding.descriptor.set);
      vk_drawing->cmd_line_with(renderpass, data);
      vk_drawing->cmd_draw_data(renderpass, data);
    }
  }

  //---------------------------
}
