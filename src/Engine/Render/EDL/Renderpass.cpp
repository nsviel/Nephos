#include "Renderpass.h"

#include <Engine/Node.h>
#include <Vulkan/Namespace.h>
#include <Engine/Render/Namespace.h>


namespace rnd::edl{

//Constructor / Destructor
Renderpass::Renderpass(eng::render::Manager* node_render){
  //---------------------------

  vk::Node* node_vulkan = node_render->get_node_vulkan();
  vk::structure::Vulkan* vk_struct = node_vulkan->get_vk_struct();

  this->shader_edl = node_render->get_shader_edl();
  this->vk_engine = node_vulkan->get_vk_engine();
  this->vk_pipeline = new vk::renderpass::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);
  this->vk_uniform = new vk::binding::Uniform(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Init function
void Renderpass::init_renderpass(){
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
void Renderpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "shader";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Renderpass::draw_edl(subpass);};

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "triangle_EDL";
  pipeline->definition.topology = "triangle";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = shader_edl->get_shader_info("EDL");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color", 0, 1, TYP_IMAGE_SAMPLER, TYP_SHADER_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth", 0, 4, TYP_IMAGE_SAMPLER, TYP_SHADER_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("EDL_param", sizeof(rnd::edl::Structure), 5, TYP_UNIFORM, TYP_SHADER_FS));
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
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

  rnd::edl::Structure* edl_param = shader_edl->get_edl_param();
  vk::structure::Renderpass* renderpass_scene = vk_engine->get_renderpass(0);
  vk::structure::Framebuffer* frame_scene = renderpass_scene->framebuffer;
  vk::structure::Pipeline* pipeline = subpass->get_pipeline();

  for(int i=0; i<subpass->vec_pipeline.size(); i++){
    vk::structure::Pipeline* pipeline = subpass->vec_pipeline[i];
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);
  }

  shader_edl->update_shader();
  vk_uniform->update_uniform("EDL_param", &pipeline->binding, *edl_param);

  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->command, pipeline);
  vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->command, pipeline, pipeline->binding.descriptor.set);

  //---------------------------
}
void Renderpass::draw_canvas(vk::structure::Subpass* subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass->command_buffer->command);
  vk_drawer->cmd_draw_data(subpass->command_buffer->command, vk_engine->get_canvas());

  //---------------------------
}

}
