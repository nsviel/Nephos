#include "EDL.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::postprocess::subpass{

//Constructor / Destructor
EDL::EDL(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);
  this->vk_edl = new vk::postprocess::pipeline::EDL(vk_struct);
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
  subpass->draw_task = [this](vk::structure::Subpass* subpass){this->draw_edl(*subpass);};
  subpass->update_sampler = [this](vk::structure::Subpass* subpass) {this->update_sampler(*subpass);};

  //Subpass pipelines
  vk_edl->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void EDL::draw_edl(vk::structure::Subpass& subpass){
  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["edl"];
  //---------------------------

  this->bind_pipeline(subpass, *pipeline);
  this->update_descriptor(subpass, *pipeline);
  this->draw_canvas(subpass);

  //---------------------------
}
void EDL::update_sampler(vk::structure::Subpass& subpass){
  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["edl"];
  //---------------------------

  std::shared_ptr<vk::descriptor::structure::Sampler> sampler_color = vk_sampler->query_sampler(pipeline->descriptor.descriptor_set, "tex_color");
  std::shared_ptr<vk::descriptor::structure::Sampler> sampler_depth = vk_sampler->query_sampler(pipeline->descriptor.descriptor_set, "tex_depth");

  vk::structure::Framebuffer& framebuffer = vk_struct->render.renderpass.geometry.framebuffer;
  sampler_color->image = std::make_unique<vk::structure::Image>(framebuffer.color);
  sampler_depth->image = std::make_unique<vk::structure::Image>(framebuffer.depth);

  //---------------------------
  vk_sampler->actualize_sampler(pipeline->descriptor.descriptor_set);
}

//Subfunction
void EDL::bind_pipeline(vk::structure::Subpass& subpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, pipeline);
  vk_viewport->cmd_viewport(subpass.command_buffer->handle);

  //---------------------------
}
void EDL::update_descriptor(vk::structure::Subpass& subpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  //Update parameters
  vk::postprocess::EDL& edl_struct = vk_struct->render.pipeline.edl;
  edl_struct.tex_width = vk_struct->window.window.dimension.x;
  edl_struct.tex_height = vk_struct->window.window.dimension.y;
  vk_uniform->update_uniform("EDL_param", pipeline.descriptor.descriptor_set, edl_struct);

  //Bind descriptor set
  vk_descriptor_set->bind_descriptor_set(subpass.command_buffer->handle, pipeline, pipeline.descriptor.descriptor_set);

  //---------------------------
}
void EDL::draw_canvas(vk::structure::Subpass& subpass){
  //---------------------------


  vk_drawer->cmd_draw_data(subpass.command_buffer->handle, *vk_struct->core.data.canvas);

  //---------------------------
}

}
