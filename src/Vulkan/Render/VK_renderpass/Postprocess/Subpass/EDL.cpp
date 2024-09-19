#include "EDL.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::edl{

//Constructor / Destructor
EDL::EDL(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);
  this->vk_factory = new vk::render::pipeline::Factory(vk_struct);
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);

  //---------------------------
}
EDL::~EDL(){}

//Init function
void EDL::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Subpass object
  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->index = 0;
  subpass->source = VK_SUBPASS_EXTERNAL;
  subpass->target = vk::renderpass::SHADER;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){this->draw_edl(*subpass);};

  //Subpass pipelines
  vk_factory->add_pipeline_edl(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void EDL::draw_edl(vk::structure::Subpass& subpass){
  //---------------------------

  this->update_binding(subpass);
  this->draw_canvas(subpass);

  //---------------------------
}

//Subfunction
void EDL::update_binding(vk::structure::Subpass& subpass){
  //---------------------------

  //Bind pipeline
  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["edl"];
  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, *pipeline);



  vk::structure::Framebuffer& frame_scene = vk_struct->render.renderpass.geometry.framebuffer;

  for(auto& [name, pipeline] : subpass.map_pipeline){
    vk_sampler->actualize_sampler(pipeline->descriptor.descriptor_set, pipeline->descriptor.layout, &frame_scene.color);
    vk_sampler->actualize_sampler(pipeline->descriptor.descriptor_set, pipeline->descriptor.layout, &frame_scene.depth);
  }

  //vk_shader->update_shader();
  vk::pipeline::edl::Structure& edl_struct = vk_struct->render.pipeline.edl;
  edl_struct.tex_width = vk_struct->window.window.dimension.x;
  edl_struct.tex_height = vk_struct->window.window.dimension.y;

  vk_uniform->update_uniform("EDL_param", pipeline->descriptor.descriptor_set, edl_struct);


  vk_descriptor_set->bind_descriptor_set(subpass.command_buffer->handle, *pipeline, pipeline->descriptor.descriptor_set);

  //---------------------------
}
void EDL::draw_canvas(vk::structure::Subpass& subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass.command_buffer->handle);
  vk_drawer->cmd_draw_data(subpass.command_buffer->handle, *vk_struct->core.data.canvas);

  //---------------------------
}

}
