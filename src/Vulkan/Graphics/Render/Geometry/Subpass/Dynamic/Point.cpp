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
  this->vk_data = new vk::data::Retriever(vk_struct);
  this->vk_storage = new vk::descriptor::Storage_image(vk_struct);
  this->vk_descriptor = new vk::pipeline::Descriptor(vk_struct);

  //---------------------------
}
Point::~Point(){}

//Main function
void Point::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Subpass object
  std::shared_ptr<vk::structure::Subpass> subpass = std::make_shared<vk::structure::Subpass>();
  subpass->index = 3;
  subpass->source = 2;
  subpass->draw_task = [this](vk::structure::Render& render){this->draw_subpass(render);};

  //Subpass pipeline
  vk_point->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Point::draw_subpass(vk::structure::Render& render){
  //---------------------------

  render.pipeline = render.subpass->map_pipeline["dynamic_point"];

  this->bind_pipeline(render);

  for(auto& [uid, vk_object] : vk_struct->core.data.map_object){
    if(!check_data(*vk_object, utl::topology::DYNAMIC_POINT)) continue;

    render.object = vk_object;


    vk::compute::dtc::Recorder recorder(vk_struct);
    recorder.run_compute(*vk_object);


    render.descriptor_set = vk_descriptor->query_descriptor_set(*render.pipeline);

    this->update_uniform(render);
    this->update_storage(render);
    this->draw_data(render);

    render.descriptor_set->is_available = true;
  }

  //---------------------------
}

//Subfunction
void Point::bind_pipeline(vk::structure::Render& render){
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(render.command_buffer->handle, *render.pipeline);
  vk_viewport->cmd_viewport(render.command_buffer->handle);

  //---------------------------
}
void Point::update_uniform(vk::structure::Render& render){
  utl::base::Data& data = *render.object->data;
  utl::base::Pose& pose = *render.object->pose;
  //---------------------------

  //MVP
  vk::geometry::MVP mvp;
  mvp.model = glm::transpose(pose.model);
  mvp.view = vk_struct->core.presentation.view;
  mvp.projection = vk_struct->core.presentation.projection;
  vk_uniform->update_uniform("mvp", *render.descriptor_set, mvp);

  //Topology width
  vk_uniform->update_uniform("width", *render.descriptor_set, data.topology.width);

  //---------------------------
}
void Point::update_storage(vk::structure::Render& render){
  //---------------------------

  std::shared_ptr<vk::structure::Storage_image> storage_cloud = vk_storage->query_storage(*render.descriptor_set, "tex_cloud");
  std::shared_ptr<vk::structure::Texture> tex_cloud = vk_data->retrieve_vk_texture(*render.object, "cloud");
  vk_storage->actualize_storage(*render.descriptor_set, *storage_cloud, tex_cloud->surface);

  //---------------------------
}
void Point::draw_data(vk::structure::Render& render){
  //---------------------------

  vk_pipeline->cmd_bind_descriptor_set(render.command_buffer->handle, *render.pipeline, *render.descriptor_set);
  vk_drawer->cmd_draw_vertex(render.command_buffer->handle, *render.object);

  //---------------------------
}
bool Point::check_data(vk::structure::Object& vk_object, int topology){
  utl::base::Data& data = *vk_object.data;
  //---------------------------

  if(data.topology.type != topology) return false;
  if(data.is_visible == false) return false;
  if(data.rgba.empty()) return false;

  //---------------------------
  return true;
}

}
