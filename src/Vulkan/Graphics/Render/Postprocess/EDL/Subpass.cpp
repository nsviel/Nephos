#include "Subpass.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::gfx::edl{

//Constructor / Destructor
Subpass::Subpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);
  this->vk_edl = new vk::gfx::edl::Pipeline(vk_struct);
  this->vk_pipeline = new vk::pipeline::gfx::Pipeline(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_descriptor = new vk::pipeline::Descriptor(vk_struct);
  this->vk_drawer = new vk::data::Vertex(vk_struct);

  //---------------------------
}
Subpass::~Subpass(){}

//Init function
void Subpass::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Subpass object
  std::shared_ptr<vk::structure::Subpass> subpass = std::make_shared<vk::structure::Subpass>();
  subpass->index = 0;
  subpass->source = VK_SUBPASS_EXTERNAL;
  subpass->draw_task = [this](std::shared_ptr<vk::structure::Render> render){this->draw_subpass(render);};
  subpass->update_sampler = [this](vk::structure::Subpass& subpass){this->update_sampler(subpass);};

  //Subpass pipelines
  vk_edl->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Subpass::draw_subpass(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  render->pipeline = render->subpass->map_pipeline["edl"];
  render->descriptor_set = vk_descriptor->query_descriptor_set(*render->pipeline);

  this->bind_pipeline(render);
  this->update_uniform(render);
  this->update_sampler(render);
  this->draw_data(render);


  //---------------------------
}
void Subpass::update_sampler(vk::structure::Subpass& subpass){
  //---------------------------



  //---------------------------
}

//Subfunction
void Subpass::bind_pipeline(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(render->command_buffer->handle, *render->pipeline);

  //---------------------------
}
void Subpass::update_uniform(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vk::gfx::edl::Structure& edl_struct = vk_struct->graphics.render.edl_struct;
  edl_struct.tex_width = render->framebuffer.current->width;
  edl_struct.tex_height = render->framebuffer.current->height;
  vk_uniform->update_uniform("parameter", *render->descriptor_set, edl_struct);

  //---------------------------
}
void Subpass::update_sampler(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  std::shared_ptr<vk::structure::Sampler> sampler_color = vk_sampler->query_sampler(*render->descriptor_set, "tex_color");
  std::shared_ptr<vk::structure::Sampler> sampler_depth = vk_sampler->query_sampler(*render->descriptor_set, "tex_depth");

  sampler_color->image = std::make_shared<vk::structure::Image>(render->framebuffer.previous->color);
  sampler_depth->image = std::make_shared<vk::structure::Image>(render->framebuffer.previous->depth);

  //---------------------------
  vk_sampler->actualize_sampler(*render->descriptor_set);
}
void Subpass::draw_data(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vk_pipeline->cmd_bind_descriptor_set(render->command_buffer->handle, *render->pipeline, *render->descriptor_set);
  vk_drawer->cmd_draw_vertex(render->command_buffer->handle, *vk_struct->core.data.canvas);

  //---------------------------
}

}
