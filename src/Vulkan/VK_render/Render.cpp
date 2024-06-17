#include "Render.h"

#include <Vulkan/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Render::Render(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->shader_edl = new vk::render::edl::Shader(vk_struct);
  this->shader_scene = new vk::render::scene::Shader(vk_struct);

  this->rp_scene = new vk::render::scene::Renderpass(vk_struct);
  this->rp_edl = new vk::render::edl::Renderpass(vk_struct);
  this->rp_gui = new vk::render::gui::Renderpass(vk_struct);

  //---------------------------
}
Render::~Render(){}

//Main function
void Render::init(){
  //---------------------------

  rp_scene->init_renderpass();
  rp_edl->init_renderpass();
  if(!vk_struct->param.headless) rp_gui->init_renderpass();

  //---------------------------
}

}
