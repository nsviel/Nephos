#include "EDL.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
EDL::EDL(vk::Node* node_vulkan){
  //---------------------------

  vk::render::Node* node_render = node_vulkan->get_node_render();
  vk::structure::Vulkan* struct_vulkan = node_vulkan->get_struct_vulkan();

  this->shader_edl = node_render->get_shader_edl();
  this->vk_graphical = node_vulkan->get_vk_graphical();
  this->vk_pipeline = new vk::renderpass::Pipeline(struct_vulkan);
  this->vk_viewport = new vk::draw::Viewport(struct_vulkan);
  this->vk_descriptor = new vk::binding::Descriptor(struct_vulkan);
  this->vk_drawing = new vk::draw::Graphical(struct_vulkan);
  this->vk_uniform = new vk::binding::Uniform(struct_vulkan);

  //---------------------------
}
EDL::~EDL(){}

//Init function
void EDL::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "edl";
  renderpass->target = "graphics";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_graphical->add_renderpass_description(renderpass);
}
void EDL::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "shader";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){EDL::draw_edl(subpass);};

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "triangle_EDL";
  pipeline->definition.topology = "triangle";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = shader_edl->get_shader_info("EDL");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color", 0, 1, TYP_IMAGE_SAMPLER, TYP_SHADER_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth", 0, 4, TYP_IMAGE_SAMPLER, TYP_SHADER_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("EDL_param", sizeof(eng::shader::EDL_param), 5, TYP_UNIFORM, TYP_SHADER_FS));
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void EDL::draw_edl(vk::structure::Subpass* subpass){
  //---------------------------

  this->update_binding(subpass);
  this->draw_command(subpass);

  //---------------------------
}
void EDL::update_binding(vk::structure::Subpass* subpass){
  //---------------------------

  eng::shader::EDL_param* edl_param = shader_edl->get_edl_param();
  vk::structure::Renderpass* renderpass_scene = vk_graphical->get_renderpass(0);
  vk::structure::Framebuffer* frame_scene = renderpass_scene->framebuffer;
  vk::structure::Pipeline* pipeline = subpass->get_pipeline();

  for(int i=0; i<subpass->vec_pipeline.size(); i++){
    vk::structure::Pipeline* pipeline = subpass->vec_pipeline[i];
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
    vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);
  }

  shader_edl->update_shader();
  vk_uniform->update_uniform("EDL_param", &pipeline->binding, *edl_param);

  //---------------------------
}
void EDL::draw_command(vk::structure::Subpass* subpass){
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline();

  vk_viewport->cmd_viewport(subpass->command_buffer->command);
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->command, pipeline);
  vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->command, pipeline, pipeline->binding.descriptor.set);
  vk_drawing->cmd_draw_data(subpass->command_buffer->command, vk_graphical->get_canvas());

  //---------------------------
}

}
