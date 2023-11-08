#include "RP_edl.h"

#include <Engine.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <VK_drawing/VK_viewport.h>
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

  this->edl_shader = eng_shader->get_edl_shader();
  this->vk_engine = engine->get_vk_engine();
  this->vk_render = vk_engine->get_vk_render();
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_viewport = new VK_viewport(vk_engine);
  this->vk_descriptor = new VK_descriptor(vk_engine);
  this->vk_drawing = new VK_drawing(vk_engine);
  this->vk_uniform = new VK_uniform(vk_engine);

  //---------------------------
}
RP_edl::~RP_edl(){}

//Init function
void RP_edl::init_renderpass(){
  //---------------------------

  //Renderpass
  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "edl";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_render->add_renderpass_description(renderpass);
}
void RP_edl::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  subpass->target = "shader";
  subpass->draw_task = [this](Struct_subpass* subpass){RP_edl::draw_edl(subpass);};

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
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void RP_edl::draw_edl(Struct_subpass* subpass){
  //---------------------------

  this->update_descriptor(subpass);
  this->draw_command(subpass);

  //---------------------------
}
void RP_edl::update_descriptor(Struct_subpass* subpass){
  //---------------------------

  Struct_renderpass* renderpass_scene = vk_engine->get_renderpass(0);
  Struct_framebuffer* frame_scene = renderpass_scene->framebuffer;

  for(int i=0; i<subpass->vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = subpass->vec_pipeline[i];
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);
  }

  //---------------------------
}
void RP_edl::draw_command(Struct_subpass* subpass){
  //---------------------------

  EDL_param* edl_param = edl_shader->get_edl_param();
  Struct_pipeline* pipeline = subpass->get_pipeline();

  vk_viewport->cmd_viewport(subpass);
  vk_pipeline->cmd_bind_pipeline(subpass, pipeline);
  edl_shader->update_shader();
  vk_uniform->update_uniform("EDL_param", &pipeline->binding, *edl_param);
  vk_descriptor->cmd_bind_descriptor(subpass, pipeline, pipeline->binding.descriptor.set);
  vk_drawing->cmd_draw_data(subpass, vk_render->get_canvas());

  //---------------------------
}
