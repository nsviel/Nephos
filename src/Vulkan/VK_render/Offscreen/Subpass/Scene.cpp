#include "Scene.h"

#include <Vulkan/Namespace.h>


namespace vk::render::offscreen{

//Constructor / Destructor
Scene::Scene(vk::Structure* vk_struct, vk::render::offscreen::Shader* vk_shader){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_drawer = new vk::render::offscreen::Drawer(vk_struct);
  this->vk_pipeline = new vk::render::pipeline::Topology(vk_struct, vk_shader);

  //---------------------------
}
Scene::~Scene(){}

//Main function
void Scene::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = vk::renderpass::SHADER;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){vk_drawer->draw_scene(subpass);};

  vk_pipeline->add_pipeline_line(subpass);
  vk_pipeline->add_pipeline_point(subpass);
  vk_pipeline->add_pipeline_triangle(subpass);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

}
