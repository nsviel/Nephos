#include "Renderpass.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::edl{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct, vk::render::edl::Shader* vk_shader){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_shader = vk_shader;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);
  this->vk_drawer = new vk::render::edl::Drawer(vk_struct, vk_shader);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Init function
void Renderpass::init(){
  //---------------------------

  vk_shader->build_shader_info();
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  this->create_renderpass(renderpass);
  this->create_subpass(renderpass);

  //---------------------------
}

//Init function
void Renderpass::create_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  renderpass->name = "edl";
  vk_struct->render.vec_renderpass.push_back(renderpass);

  //---------------------------

}
void Renderpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = vk::renderpass::SHADER;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){vk_drawer->draw_edl(subpass);};

  this->create_pipeline_edl(subpass);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}
void Renderpass::create_pipeline_edl(vk::structure::Subpass* subpass){
  //---------------------------

  //Shader
  utl::shader::Info* shader_info = vk_shader->get_shader_info("EDL");

  //Pipeline
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->info.name = "triangle_EDL";
  pipeline->info.topology = utl::topology::TRIANGLE;
  pipeline->info.shader = shader_info;
  pipeline->info.vec_attribut.push_back(vk::pipeline::XYZ);
  pipeline->info.vec_attribut.push_back(vk::pipeline::UV);

  //Descriptor
  vk::binding::structure::Required sampler_color = vk_sampler->sampler_color();
  vk::binding::structure::Required sampler_depth = vk_sampler->sampler_depth();
  vk::binding::structure::Required uniform_edl = vk_uniform->uniform_edl();

  pipeline->binding.vec_required_binding.push_back(sampler_color);
  pipeline->binding.vec_required_binding.push_back(sampler_depth);
  pipeline->binding.vec_required_binding.push_back(uniform_edl);

  //---------------------------
  subpass->vec_pipeline.push_back(pipeline);
}

}
