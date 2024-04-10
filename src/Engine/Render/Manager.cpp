#include "Manager.h"

#include <Engine/Namespace.h>
#include <Render/Namespace.h>


namespace eng::render{

//Constructor / Destructor
Manager::Manager(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_utility = node_engine->get_node_utility();
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_operation = node_engine->get_node_operation();
  this->node_camera = node_engine->get_node_camera();

  //Child
  this->shader_edl = new rnd::edl::Shader(this);
  this->shader_scene = new rnd::scene::Shader(this);

  this->rp_scene = new rnd::scene::Renderpass(this);
  this->rp_edl = new rnd::edl::Renderpass(this);
  this->rp_gui = new rnd::gui::Renderpass(this);

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
