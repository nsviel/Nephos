#include "Point.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::geometry::subpass::topology{

//Constructor / Destructor
Point::Point(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_drawer = new vk::data::Vertex(vk_struct);
  this->vk_point = new vk::geometry::pipeline::topology::Point(vk_struct);

  //---------------------------
}
Point::~Point(){}

//Main function
void Point::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Subpass object
  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->index = 0;
  subpass->source = VK_SUBPASS_EXTERNAL;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){this->draw_subpass(*subpass);};

  //Subpass pipeline
  vk_point->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Point::draw_subpass(vk::structure::Subpass& subpass){
  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["point"];
  //---------------------------

  this->bind_pipeline(subpass, *pipeline);

  for(auto& [uid, vk_object] : vk_struct->core.data.map_object){
    if(!check_data(*vk_object, utl::topology::POINT)) continue;
    this->update_uniform(subpass, *vk_object, *pipeline);
    this->draw_data(*vk_object, subpass);
  }

  //---------------------------
}

//Subfunction
void Point::bind_pipeline(vk::structure::Subpass& subpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, pipeline);
  vk_viewport->cmd_viewport(subpass.command_buffer->handle);

  //---------------------------
}
void Point::update_uniform(vk::structure::Subpass& subpass, vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline){
  utl::base::Data& data = *vk_object.data;
  utl::base::Pose& pose = *vk_object.pose;
  //---------------------------

  //MVP
  vk::geometry::MVP machin;
  machin.model = glm::transpose(pose.model);
  machin.view = vk_struct->core.presentation.view;
  machin.projection = vk_struct->core.presentation.projection;
  vk_uniform->update_uniform("mvp", vk_object.descriptor_set, machin);

  //Topology width
  vk_uniform->update_uniform("width", vk_object.descriptor_set, data.topology.width);

  //Descriptor set
  vk_descriptor_set->bind_descriptor_set(subpass.command_buffer->handle, pipeline, vk_object.descriptor_set);

  //---------------------------
}
void Point::draw_data(vk::structure::Object& vk_object, vk::structure::Subpass& subpass){
  //---------------------------

  vk_drawer->cmd_draw_vertex(subpass.command_buffer->handle, vk_object);

  //---------------------------
}
bool Point::check_data(vk::structure::Object& vk_object, int topology){
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