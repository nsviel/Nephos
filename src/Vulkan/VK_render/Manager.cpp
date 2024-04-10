#include "Manager.h"

#include <Vulkan/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Manager::Manager(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->shader_edl = new vk::render::edl::Shader(vk_struct);
  this->shader_scene = new vk::render::scene::Shader(vk_struct);

  this->rp_scene = new vk::render::scene::Renderpass(vk_struct);
  this->rp_edl = new vk::render::edl::Renderpass(vk_struct);
  this->rp_gui = new vk::render::gui::Renderpass(vk_struct);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  rp_scene->init_renderpass();
  rp_edl->init_renderpass();
  rp_gui->init_renderpass();

  //---------------------------
}

}
