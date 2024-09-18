#include "Scene.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::geometry{

//Constructor / Destructor
Scene::Scene(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_drawer = new vk::draw::Drawer(vk_struct);
  this->vk_factory = new vk::render::pipeline::Factory(vk_struct);

  //---------------------------
}
Scene::~Scene(){}

//Main function
void Scene::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Set subpass object
  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->index = 0;
  subpass->source = VK_SUBPASS_EXTERNAL;
  subpass->target = vk::renderpass::SHADER;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){this->draw_subpass(*subpass);};

  //Set pipeline
  vk_factory->add_pipeline_line(*subpass);
  vk_factory->add_pipeline_point(*subpass);
  vk_factory->add_pipeline_triangle(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Scene::draw_subpass(vk::structure::Subpass& subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass.command_buffer->handle);
  this->cmd_draw_point(subpass);
  this->cmd_draw_line(subpass);
  this->cmd_draw_triangle(subpass);

  //---------------------------
}

//Subfunction
void Scene::cmd_draw_point(vk::structure::Subpass& subpass){
  //---------------------------

  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["point"];
  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, *pipeline);

  //Bind and draw vertex buffers
  for(auto& vk_object : vk_struct->core.data.list_vk_object){
    utl::base::Data& data = *vk_object->data;
    utl::base::Pose& pose = *vk_object->pose;

    if(check_data(data, utl::topology::POINT)){
      vk_uniform->update_uniform("mvp", vk_object->descriptor_set, pose.mvp);



      vk::pipeline::topology::Structure machin;
      machin.model = glm::transpose(pose.model);
      machin.view = vk_struct->core.presentation.view;
      machin.projection = vk_struct->core.presentation.projection;
      vk_uniform->update_uniform("mvp_str", vk_object->descriptor_set, machin);




      vk_uniform->update_uniform("point_size", vk_object->descriptor_set, data.topology.width);
      vk_descriptor_set->bind_descriptor_set(subpass.command_buffer->handle, *pipeline, vk_object->descriptor_set);
      vk_drawer->cmd_draw_data(subpass.command_buffer->handle, *vk_object);
    }
  }

  //---------------------------
}
void Scene::cmd_draw_line(vk::structure::Subpass& subpass){
  //---------------------------

  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["line"];
  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, *pipeline);

  //Bind and draw vertex buffers
  for(auto& vk_object : vk_struct->core.data.list_vk_object){
    utl::base::Data& data = *vk_object->data;
    utl::base::Pose& pose = *vk_object->pose;

    if(check_data(data, utl::topology::LINE)){
      vk_uniform->update_uniform("mvp", vk_object->descriptor_set, pose.mvp);
      vk_descriptor_set->bind_descriptor_set(subpass.command_buffer->handle, *pipeline, vk_object->descriptor_set);
      vk_drawer->cmd_line_with(subpass.command_buffer->handle, *vk_object);
      vk_drawer->cmd_draw_data(subpass.command_buffer->handle, *vk_object);
    }
  }

  //---------------------------
}
void Scene::cmd_draw_triangle(vk::structure::Subpass& subpass){
  //---------------------------

  std::shared_ptr<vk::structure::Pipeline> pipeline = subpass.map_pipeline["triangle"];
  vk_pipeline->cmd_bind_pipeline(subpass.command_buffer->handle, *pipeline);

  //Bind and draw vertex buffers
  for(auto& vk_object : vk_struct->core.data.list_vk_object){
    utl::base::Data& data = *vk_object->data;
    utl::base::Pose& pose = *vk_object->pose;

    if(check_data(data, utl::topology::TRIANGLE)){
      vk_uniform->update_uniform("mvp", vk_object->descriptor_set, pose.mvp);
      vk_descriptor_set->bind_descriptor_set(subpass.command_buffer->handle, *pipeline, vk_object->descriptor_set);
      vk_drawer->cmd_draw_data(subpass.command_buffer->handle, *vk_object);
    }
  }

  //---------------------------
}
bool Scene::check_data(utl::base::Data& data, int typology){
  //---------------------------

  if(data.topology.type != typology) return false;
  if(data.is_visible == false) return false;
  if(data.xyz.empty()) return false;
  if(data.rgba.empty()) return false;
  if(data.rgba.size() != data.xyz.size()) return false;

  //---------------------------
  return true;
}

}
