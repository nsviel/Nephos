#include "Line.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::geometry::subpass::topology{

//Constructor / Destructor
Line::Line(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::pipeline::gfx::Pipeline(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_vertex = new vk::data::Vertex(vk_struct);
  this->vk_line = new vk::geometry::pipeline::topology::Line(vk_struct);
  this->vk_descriptor = new vk::pipeline::Descriptor(vk_struct);

  //---------------------------
}
Line::~Line(){}

//Main function
void Line::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Subpass object
  std::shared_ptr<vk::structure::Subpass> subpass = std::make_shared<vk::structure::Subpass>();
  subpass->index = 1;
  subpass->source = 0;
  subpass->draw_task = [this](std::shared_ptr<vk::structure::Render> render){this->draw_subpass(render);};

  //Subpass pipeline
  vk_line->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Line::draw_subpass(std::shared_ptr<vk::structure::Render> render){
  render->pipeline = render->subpass->map_pipeline["line"];
  //---------------------------

  this->bind_pipeline(render);

  for(auto& [uid, vk_object] : vk_struct->core.data.map_object){
    if(!check_data(*vk_object, utl::topology::LINE)) continue;
    render->object = vk_object;
    render->descriptor_set = vk_descriptor->query_descriptor_set(*render->pipeline);

    this->update_uniform(render);
    this->draw_data(render);

  }

  //---------------------------
}

//Subfunction
void Line::bind_pipeline(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(render->command_buffer->handle, *render->pipeline);

  //---------------------------
}
void Line::update_uniform(std::shared_ptr<vk::structure::Render> render){
  utl::base::Data& data = *render->object->data;
  utl::base::Pose& pose = *render->object->pose;
  //---------------------------

  //MVP
  vk::geometry::MVP mvp;
  mvp.model = glm::transpose(pose.model);
  mvp.view = vk_struct->core.presentation.view;
  mvp.projection = vk_struct->core.presentation.projection;
  vk_uniform->update_uniform("mvp", *render->descriptor_set, mvp);

  //---------------------------
}
void Line::draw_data(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vk_pipeline->cmd_bind_descriptor_set(render->command_buffer->handle, *render->pipeline, *render->descriptor_set);
  vk_vertex->cmd_line_with(render->command_buffer->handle, *render->object);
  vk_vertex->cmd_draw_vertex(render->command_buffer->handle, *render->object);

  //---------------------------
}
bool Line::check_data(vk::structure::Object& vk_object, int topology){
  utl::base::Data& data = *vk_object.data;
  //---------------------------

  if(data.topology.type != topology) return false;
  if(data.is_visible == false) return false;
  if(data.xyz.empty()) return false;
  if(data.rgba.empty()) return false;
  if(data.rgba.size() != data.xyz.size()) return false;

  //---------------------------
  return true;
}

}
