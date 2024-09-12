#include "Render.h"

#include <Vulkan/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Render::Render(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->shader_edl = new vk::render::edl::Shader(vk_struct);

  this->rp_scene = new vk::render::offscreen::Renderpass(vk_struct);
  this->rp_edl = new vk::render::edl::Renderpass(vk_struct);
  this->rp_gui = new vk::render::onscreen::Renderpass(vk_struct);

  //---------------------------
}
Render::~Render(){}

//Main function
void Render::init(){
  //---------------------------

  rp_scene->init();
  rp_edl->init();
  rp_gui->init();

  //---------------------------
}

}
