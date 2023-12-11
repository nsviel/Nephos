#include "RP_edl.h"

#include <Engine/Node/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_pipeline/VK_pipeline.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Vulkan/VK_drawing/VK_viewport.h>
#include <Vulkan/VK_drawing/VK_drawing.h>
#include <Vulkan/VK_binding/VK_descriptor.h>
#include <Vulkan/VK_binding/VK_uniform.h>

#include <Engine/Rendering/ENG_shader/ENG_shader.h>
#include <Engine/Rendering/ENG_shader/EDL/EDL_shader.h>
#include <Engine/Rendering/ENG_shader/EDL/EDL_param.h>


//Constructor / Destructor
RP_edl::RP_edl(Engine* engine){
  //---------------------------

  ENG_shader* eng_shader = engine->get_eng_shader();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  vk::structure::Vulkan* struct_vulkan = eng_vulkan->get_struct_vulkan();

  this->edl_shader = eng_shader->get_edl_shader();
  this->vk_engine = eng_vulkan->get_vk_engine();
  this->vk_pipeline = new VK_pipeline(struct_vulkan);
  this->vk_viewport = new VK_viewport(struct_vulkan);
  this->vk_descriptor = new VK_descriptor(struct_vulkan);
  this->vk_drawing = new VK_drawing(struct_vulkan);
  this->vk_uniform = new VK_uniform(struct_vulkan);

  //---------------------------
}
RP_edl::~RP_edl(){}

//Init function
void RP_edl::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "edl";
  renderpass->target = "graphics";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_engine->add_renderpass_description(renderpass);
}
void RP_edl::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "shader";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){RP_edl::draw_edl(subpass);};

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "triangle_EDL";
  pipeline->definition.topology = "triangle";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = edl_shader->get_shader_info("EDL");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color", 0, 1, TYP_IMAGE_SAMPLER, TYP_SHADER_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth", 0, 4, TYP_IMAGE_SAMPLER, TYP_SHADER_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("EDL_param", sizeof(EDL_param), 5, TYP_UNIFORM, TYP_SHADER_FS));
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void RP_edl::draw_edl(vk::structure::Subpass* subpass){
  //---------------------------

  this->update_descriptor(subpass);
  this->draw_command(subpass);

  //---------------------------
}
void RP_edl::update_descriptor(vk::structure::Subpass* subpass){
  //---------------------------

  vk::structure::Renderpass* renderpass_scene = vk_engine->get_renderpass(0);
  vk::structure::Framebuffer* frame_scene = renderpass_scene->framebuffer;

  for(int i=0; i<subpass->vec_pipeline.size(); i++){
    vk::structure::Pipeline* pipeline = subpass->vec_pipeline[i];
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);
  }

  //---------------------------
}
void RP_edl::draw_command(vk::structure::Subpass* subpass){
  //---------------------------

  EDL_param* edl_param = edl_shader->get_edl_param();
  vk::structure::Pipeline* pipeline = subpass->get_pipeline();

  vk_viewport->cmd_viewport(subpass->command_buffer);
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer, pipeline);
  edl_shader->update_shader();
  vk_uniform->update_uniform("EDL_param", &pipeline->binding, *edl_param);
  vk_descriptor->cmd_bind_descriptor(subpass->command_buffer, pipeline, pipeline->binding.descriptor.set);
  vk_drawing->cmd_draw_data(subpass->command_buffer, vk_engine->get_canvas());

  //---------------------------
}
