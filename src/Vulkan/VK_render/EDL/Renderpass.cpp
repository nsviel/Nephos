#include "Renderpass.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::edl{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->shader_edl = new vk::render::edl::Shader(vk_struct);
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Init function
void Renderpass::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "edl";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_struct->render.vec_renderpass.push_back(renderpass);
}
void Renderpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = vk::renderpass::SHADER;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Renderpass::draw_edl(subpass);};

  this->pipeline_edl(subpass);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}
void Renderpass::pipeline_edl(vk::structure::Subpass* subpass){
  //---------------------------

  //Shader
  utl::shader::Info* shader_info = shader_edl->get_shader_info("EDL");

  //Pipeline
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->info.name = "triangle_EDL";
  pipeline->info.topology = utl::topology::TRIANGLE;
  pipeline->info.shader = shader_info;
  pipeline->info.vec_attribut.push_back(vk::pipeline::XYZ);
  pipeline->info.vec_attribut.push_back(vk::pipeline::UV);

  //Descriptor
  vk::binding::structure::Required descriptor;
  descriptor = vk_sampler->sampler_color();
  pipeline->binding.vec_required_binding.push_back(descriptor);
  descriptor = vk_sampler->sampler_depth();
  pipeline->binding.vec_required_binding.push_back(descriptor);
  descriptor = vk_uniform->uniform_edl();
  pipeline->binding.vec_required_binding.push_back(descriptor);

  //---------------------------
  subpass->vec_pipeline.push_back(pipeline);
}

//Draw function
void Renderpass::draw_edl(vk::structure::Subpass* subpass){
  //---------------------------

  this->update_binding(subpass);
  this->draw_canvas(subpass);

  //---------------------------
}
void Renderpass::update_binding(vk::structure::Subpass* subpass){
  //---------------------------

  vk::render::edl::Structure* edl_struct = shader_edl->get_edl_struct();
  vk::structure::Renderpass* renderpass_scene = vk_struct->render.vec_renderpass[0];
  vk::structure::Framebuffer* frame_scene = renderpass_scene->framebuffer;
  vk::structure::Pipeline* pipeline = subpass->get_pipeline();

  for(int i=0; i<subpass->vec_pipeline.size(); i++){
    vk::structure::Pipeline* pipeline = subpass->vec_pipeline[i];
    vk_sampler->update_sampler(&pipeline->binding, &frame_scene->color);
    vk_sampler->update_sampler(&pipeline->binding, &frame_scene->depth);
  }

  shader_edl->update_shader();
  vk_uniform->update_uniform("EDL_param", &pipeline->binding, *edl_struct);

  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->handle, pipeline);
  vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->handle, pipeline, pipeline->binding.descriptor.set);

  //---------------------------
}
void Renderpass::draw_canvas(vk::structure::Subpass* subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass->command_buffer->handle);
  vk_drawer->cmd_draw_data(subpass->command_buffer->handle, &vk_struct->data.canvas);

  //---------------------------
}

}
