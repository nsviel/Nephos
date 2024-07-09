#include "Drawer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::edl{

//Constructor / Destructor
Drawer::Drawer(vk::Structure* vk_struct, vk::render::edl::Shader* vk_shader){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_shader = vk_shader;
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);

  //---------------------------
}
Drawer::~Drawer(){}

//Main function
void Drawer::draw_edl(vk::structure::Subpass* subpass){
  //---------------------------

  this->update_binding(subpass);
  this->draw_canvas(subpass);

  //---------------------------
}

//Subfunction
void Drawer::update_binding(vk::structure::Subpass* subpass){
  //---------------------------

  vk::render::edl::Structure* edl_struct = vk_shader->get_edl_struct();
  vk::structure::Renderpass* renderpass_scene = vk_struct->render.vec_renderpass[0];
  vk::structure::Framebuffer* frame_scene = renderpass_scene->framebuffer;
  vk::structure::Pipeline* pipeline = subpass->get_pipeline();

  for(int i=0; i<subpass->vec_pipeline.size(); i++){
    vk::structure::Pipeline* pipeline = subpass->vec_pipeline[i];
    vk_sampler->update_sampler(&pipeline->binding, &frame_scene->color);
    vk_sampler->update_sampler(&pipeline->binding, &frame_scene->depth);
  }

  vk_shader->update_shader();
  vk_uniform->update_uniform("EDL_param", &pipeline->binding, *edl_struct);

  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->handle, pipeline);
  vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->handle, pipeline, pipeline->binding.descriptor.set);

  //---------------------------
}
void Drawer::draw_canvas(vk::structure::Subpass* subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass->command_buffer->handle);
  vk_drawer->cmd_draw_data(subpass->command_buffer->handle, &vk_struct->data.canvas);

  //---------------------------
}

}
