#include "EDL.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::offscreen{

//Constructor / Destructor
EDL::EDL(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);
  this->vk_factory = new vk::render::pipeline::Factory(vk_struct);
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);

  //---------------------------
}
EDL::~EDL(){}

//Init function
void EDL::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Set subpass object
  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->index = 1;
  subpass->source = 0;
  subpass->target = vk::renderpass::SHADER;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){this->draw_subpass(*subpass);};

  //Set pipeline
  vk_factory->add_pipeline_edl(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void EDL::draw_subpass(vk::structure::Subpass& subpass){
  //---------------------------

  this->update_binding(subpass);
  this->draw_canvas(subpass);

  //---------------------------
}

//Subfunction
void EDL::update_binding(vk::structure::Subpass& subpass){
  //---------------------------

  vk::render::structure::EDL& edl_struct = vk_struct->render.edl;
  vk::structure::Renderpass* renderpass_scene = vk_struct->renderpass.vector[0];
  vk::structure::Framebuffer& frame_scene = renderpass_scene->framebuffer;
  vk::structure::Pipeline* pipeline = subpass.get_pipeline();

  for(int i=0; i<subpass.vec_pipeline.size(); i++){
    vk::structure::Pipeline* pipeline = subpass.vec_pipeline[i];
    vk_sampler->update_sampler(&pipeline->binding, &frame_scene.color);
    vk_sampler->update_sampler(&pipeline->binding, &frame_scene.depth);
  }

  //vk_shader->update_shader();
  edl_struct.tex_width = vk_struct->window.dimension.x;
  edl_struct.tex_height = vk_struct->window.dimension.y;

  vk_uniform->update_uniform("EDL_param", &pipeline->binding, edl_struct);

  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, pipeline);
  vk_descriptor->cmd_bind_descriptor(subpass.command_buffer->handle, pipeline, pipeline->binding.descriptor.set);

  //---------------------------
}
void EDL::draw_canvas(vk::structure::Subpass& subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass.command_buffer->handle);
  vk_drawer->cmd_draw_data(subpass.command_buffer->handle, *vk_struct->data.canvas);

  //---------------------------
}

}
