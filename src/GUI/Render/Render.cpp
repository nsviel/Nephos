#include "Render.h"

#include <GUI/Namespace.h>
#include <Vulkan/Namespace.h>


namespace gui{

//Constructor / Destructor
Render::Render(gui::Node* node_gui){
  //---------------------------

  vk::Node* node_vulkan = node_gui->get_node_vulkan();

  this->vk_imgui = node_vulkan->get_vk_imgui();

  //---------------------------
}
Render::~Render(){}

// Main code
void Render::new_frame(){
  //---------------------------

  vk_imgui->new_frame();

  //---------------------------
}
void Render::end_frame(){
  //---------------------------

  vk_imgui->render();

  //---------------------------
}

}
