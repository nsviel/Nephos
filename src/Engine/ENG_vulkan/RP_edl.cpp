#include "RP_edl.h"

#include <Engine.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_drawing/VK_viewport.h>
#include <VK_command/VK_command.h>
#include <VK_drawing/VK_drawing.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_binding/VK_uniform.h>

#include <ENG_shader/ENG_shader.h>
#include <ENG_shader/EDL/EDL_shader.h>
#include <ENG_shader/EDL/EDL_param.h>


//Constructor / Destructor
RP_edl::RP_edl(Engine* engine){
  //---------------------------

  ENG_shader* eng_shader = engine->get_eng_shader();

  this->vk_engine = engine->get_vk_engine();
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->edl_shader = eng_shader->get_edl_shader();
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_viewport = new VK_viewport(vk_engine);
  this->vk_descriptor = new VK_descriptor(vk_engine);
  this->vk_drawing = new VK_drawing(vk_engine);
  this->vk_uniform = new VK_uniform(vk_engine);
  this->vk_command = new VK_command(vk_engine);
  this->vk_render = vk_engine->get_vk_render();

  //---------------------------
}
RP_edl::~RP_edl(){}

//Init function
Struct_renderpass* RP_edl::init_renderpass(){
  //---------------------------

  //Renderpass
  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "edl";
  renderpass->subpass = "shader";
  renderpass->draw_task = [this](Struct_renderpass* renderpass){RP_edl::draw_edl(renderpass);};

  //Pipeline
  this->create_pipeline_edl(renderpass);

  //---------------------------
  return renderpass;
}
void RP_edl::create_pipeline_edl(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->definition.name = "triangle_EDL";
  pipeline->definition.topology = "triangle";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = edl_shader->get_shader_info("EDL");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color", 0, 1, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth", 0, 4, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("EDL_param", sizeof(EDL_param), 5, TYPE_UNIFORM, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}

//Draw function
void RP_edl::draw_edl(Struct_renderpass* renderpass){
  //---------------------------

  this->update_descriptor(renderpass);
  this->draw_command(renderpass);

  //---------------------------
}
void RP_edl::update_descriptor(Struct_renderpass* renderpass){
  //---------------------------

  Struct_frame* frame_scene = struct_vulkan->vec_renderpass[0]->get_rendering_frame();
  for(int i=0; i<renderpass->vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = renderpass->vec_pipeline[i];
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);
  }

  //---------------------------
}
void RP_edl::draw_command(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle_EDL");
  EDL_param* edl_param = edl_shader->get_edl_param();
  Struct_frame* frame_render = renderpass->get_rendering_frame();

  vk_command->start_render_pass(renderpass, frame_render, false);
  vk_viewport->cmd_viewport(renderpass);

  vk_pipeline->cmd_bind_pipeline(renderpass, "triangle_EDL");
  edl_shader->update_shader();
  vk_uniform->update_uniform("EDL_param", &pipeline->binding, *edl_param);
  vk_descriptor->cmd_bind_descriptor(renderpass, "triangle_EDL", pipeline->binding.descriptor.set);
  vk_drawing->cmd_draw_data(renderpass, vk_render->get_canvas());

  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
