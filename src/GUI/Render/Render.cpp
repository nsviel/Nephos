#include "Render.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Vulkan/Namespace.h>


namespace gui{

//Constructor / Destructor
Render::Render(gui::Node* gui){
  //---------------------------

  utl::Node* utility = gui->get_node_utility();
  eng::Node* engine = gui->get_node_engine();
  utl::element::Window* utl_window = utility->get_utl_window();

  this->vulkan = engine->get_eng_vulkan();
  //this->vulkan = new Vulkan(utl_window);
  this->vk_engine = vulkan->get_vk_engine();
  this->vk_imgui = vulkan->get_vk_imgui();

  //---------------------------
}
Render::~Render(){}

// Main code
void Render::init(){
  //---------------------------


  //---------------------------
}
void Render::render(){
  //---------------------------

  vk_imgui->render();

  //---------------------------
}
void Render::clean(){
  //---------------------------

  vk_imgui->clean();

  //---------------------------
}
void Render::new_frame(){
  //---------------------------

  vk_imgui->new_frame();

  //---------------------------
}

}
