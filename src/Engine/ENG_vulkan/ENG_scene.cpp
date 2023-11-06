#include "ENG_scene.h"

#include <Engine.h>
#include <VK_drawing/VK_renderpass.h>
#include <VK_pipeline/VK_subpass.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_drawing/VK_viewport.h>
#include <ENG_shader/Shader.h>
#include <ENG_shader/Scene/SCE_shader.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>
#include <VK_presentation/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_binding/VK_uniform.h>
#include <VK_drawing/VK_drawing.h>


//Constructor / Destructor
ENG_scene::ENG_scene(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_viewport = new VK_viewport(vk_engine);
  this->vk_subpass = new VK_subpass(vk_engine);
  this->vk_command = new VK_command(vk_engine);
  this->vk_descriptor = new VK_descriptor(vk_engine);
  this->vk_uniform = new VK_uniform(vk_engine);
  this->vk_drawing = vk_engine->get_vk_drawing();

  //---------------------------
}
ENG_scene::~ENG_scene(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Init function
Struct_renderpass* ENG_scene::init_renderpass(){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "scene";
  renderpass->subpass = "shader";
  this->create_pipeline_point(renderpass);
  this->create_pipeline_line(renderpass);

  //---------------------------
  return renderpass;
}
void ENG_scene::create_pipeline_point(Struct_renderpass* renderpass){
  //---------------------------

  Engine* engine = vk_engine->get_engine();
  Shader* shaderManager = engine->get_shaderManager();
  SCE_shader* sce_shader = shaderManager->get_sce_shader();

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "point";
  pipeline->topology = "point";
  pipeline->purpose = "graphics";
  pipeline->shader_info = sce_shader->get_shader_info("Point");
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("point_size", sizeof(int), 1, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
void ENG_scene::create_pipeline_line(Struct_renderpass* renderpass){
  //---------------------------

  Engine* engine = vk_engine->get_engine();
  Shader* shaderManager = engine->get_shaderManager();
  SCE_shader* sce_shader = shaderManager->get_sce_shader();

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "line";
  pipeline->topology = "line";
  pipeline->purpose = "graphics";
  pipeline->shader_info = sce_shader->get_shader_info("Line");
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}

//Draw function
void ENG_scene::draw_scene(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  Frame* frame = renderpass->get_rendering_frame();
  vk_command->start_render_pass(renderpass, frame, false);
  vk_viewport->cmd_viewport(renderpass);
  this->cmd_draw_scene(renderpass);
  this->cmd_draw_glyph(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
  this->time_renderpass = timer.stop_ms(t1);
}
void ENG_scene::cmd_draw_scene(Struct_renderpass* renderpass){
  list<Struct_data*> list_data_scene = vk_engine->get_list_data_scene();
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(renderpass, "point");

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
void ENG_scene::cmd_draw_glyph(Struct_renderpass* renderpass){
  list<Struct_data*> list_data_glyph = vk_engine->get_list_data_glyph();
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(renderpass, "line");

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
