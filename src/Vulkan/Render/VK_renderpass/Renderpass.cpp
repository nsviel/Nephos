#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->rp_scene = new vk::render::geometry::Renderpass(vk_struct);
  this->rp_edl = new vk::postprocess::Renderpass(vk_struct);
  this->rp_gui = new vk::present::Renderpass(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  //---------------------------

  rp_scene->init();
  rp_edl->init();
  rp_gui->init();

  //---------------------------
}

}
