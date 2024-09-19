#include "Line.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::geometry::subpass::topology{

//Constructor / Destructor
Line::Line(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);
  this->vk_line = new vk::geometry::pipeline::topology::Line(vk_struct);

  //---------------------------
}
Line::~Line(){}

//Main function
void Line::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Subpass object
  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->index = 1;
  subpass->source = 0;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){this->draw_subpass(*subpass);};

  //Subpass pipeline
  vk_line->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Line::draw_subpass(vk::structure::Subpass& subpass){
  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["line"];
  //---------------------------

  this->bind_pipeline(subpass, *pipeline);

  for(auto& vk_object : vk_struct->core.data.list_vk_object){
    if(!check_data(*vk_object, utl::topology::LINE, false)) continue;
    this->update_uniform(subpass, *vk_object, *pipeline);
    this->draw_data(*vk_object, subpass);
  }

  //---------------------------
}

//Subfunction
void Line::bind_pipeline(vk::structure::Subpass& subpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, pipeline);
  vk_viewport->cmd_viewport(subpass.command_buffer->handle);

  //---------------------------
}
void Line::update_uniform(vk::structure::Subpass& subpass, vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline){
  utl::base::Data& data = *vk_object.data;
  utl::base::Pose& pose = *vk_object.pose;
  //---------------------------

  //MVP
  vk::geometry::MVP machin;
  machin.model = glm::transpose(pose.model);
  machin.view = vk_struct->core.presentation.view;
  machin.projection = vk_struct->core.presentation.projection;
  vk_uniform->update_uniform("mvp", vk_object.descriptor_set, machin);

  //Descriptor set
  vk_descriptor_set->bind_descriptor_set(subpass.command_buffer->handle, pipeline, vk_object.descriptor_set);

  //---------------------------
}
void Line::draw_data(vk::structure::Object& vk_object, vk::structure::Subpass& subpass){
  //---------------------------

  vk_drawer->cmd_line_with(subpass.command_buffer->handle, vk_object);
  vk_drawer->cmd_draw_data(subpass.command_buffer->handle, vk_object);

  //---------------------------
}
bool Line::check_data(vk::structure::Object& vk_object, int topology, bool dynamic){
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
