#include "Render.h"

#include <Vulkan/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Render::Render(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->rp_scene = new vk::geometry::Renderpass(vk_struct);
  this->rp_edl = new vk::postprocess::Renderpass(vk_struct);
  this->rp_gui = new vk::present::Renderpass(vk_struct);

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
void Render::loop(){
  //---------------------------

  vk_struct->core.queue.presentation->make_rendering();

  //---------------------------
}

}