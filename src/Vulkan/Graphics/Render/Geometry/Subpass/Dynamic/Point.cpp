#include "Point.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::geometry::subpass::dynamic{

//Constructor / Destructor
Point::Point(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::render::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_drawer = new vk::data::Vertex(vk_struct);
  this->vk_point = new vk::geometry::pipeline::dynamic::Point(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);
  this->vk_data = new vk::data::Function(vk_struct);
  this->vk_storage = new vk::descriptor::Storage_image(vk_struct);

  //---------------------------
}
Point::~Point(){}

//Main function
void Point::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Subpass object
  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->index = 3;
  subpass->source = 2;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){this->draw_subpass(*subpass);};

  //Subpass pipeline
  vk_point->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Point::draw_subpass(vk::structure::Subpass& subpass){
  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["dynamic_point"];
  //---------------------------

  this->bind_pipeline(subpass, *pipeline);

  for(auto& [uid, vk_object] : vk_struct->core.data.map_object){
    if(!check_data(*vk_object, utl::topology::DYNAMIC_POINT)) continue;


    //vk::compute::dtc::Recorder recorder(vk_struct);
    //recorder.run_compute(*vk_object);


    this->update_uniform(*vk_object, *pipeline);
    this->update_sampler(*vk_object, *pipeline, subpass);
    this->draw_data(*vk_object, *pipeline, subpass);


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
void Point::update_uniform(vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline){
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

  //Update parameters
  std::shared_ptr<vk::structure::Texture> tex_depth = vk_data->retrieve_vk_texture(vk_object, "Depth");
  vk::geometry::Dynamic dyn_struct;
  dyn_struct.tex_depth_width = tex_depth->image->width;
  dyn_struct.tex_depth_height = tex_depth->image->height;
  vk_uniform->update_uniform("parameter", vk_object.descriptor_set, dyn_struct);

  //---------------------------
}
void Point::update_sampler(vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline, vk::structure::Subpass& subpass){
  //---------------------------
/*
  //Color texture
  std::shared_ptr<vk::structure::Sampler> sampler_color = vk_sampler->query_sampler(vk_object.descriptor_set, "tex_color");
  std::shared_ptr<vk::structure::Sampler> sampler_depth = vk_sampler->query_sampler(vk_object.descriptor_set, "tex_depth");
  if(!sampler_color || !sampler_depth) return;

  std::shared_ptr<vk::structure::Texture> texture_color = vk_data->retrieve_vk_texture(vk_object, "Color");
  std::shared_ptr<vk::structure::Texture> texture_depth = vk_data->retrieve_vk_texture(vk_object, "Depth");
  if(!texture_color || !texture_depth) return;

  vk_sampler->actualize_sampler(vk_object.descriptor_set, *sampler_color, texture_color->surface);
  vk_sampler->actualize_sampler(vk_object.descriptor_set, *sampler_depth, texture_depth->surface);
*/
/*
  std::shared_ptr<vk::structure::Storage_image> storage_cloud = vk_storage->query_storage(vk_object.descriptor_set, "tex_cloud");
  std::shared_ptr<vk::structure::Texture> tex_cloud = vk_data->retrieve_vk_texture(vk_object, "cloud");
  vk_storage->actualize_storage(vk_object.descriptor_set, *storage_cloud, tex_cloud->surface);
*/
  //---------------------------
}
void Point::draw_data(vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline, vk::structure::Subpass& subpass){
  //---------------------------

  vk_pipeline->cmd_bind_descriptor_set(subpass.command_buffer->handle, pipeline, vk_object.descriptor_set);
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
