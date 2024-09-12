#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::offscreen{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct, vk::render::offscreen::Shader* vk_shader){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_shader = vk_shader;
  this->vk_scene = new vk::render::offscreen::Scene(vk_struct, vk_shader);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  //---------------------------

  vk_shader->build_shader_info();
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  this->create_renderpass(renderpass);
  vk_scene->create_subpass(renderpass);

  //---------------------------
}

//Subfunction
void Renderpass::create_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  renderpass->name = "scene";
  vk_struct->render.vec_renderpass.push_back(renderpass);

  //---------------------------
}

}
