#include "Node.h"

#include <Application/Node.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Camera/Namespace.h>
#include <Render/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Dynamic/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  //Dependancy
  this->node_profiler = node_app->get_node_profiler();

  //Child
  this->thread_pool = new utl::thread::Pool(50);
  this->node_vulkan = new vk::Node(node_app);

  this->node_camera = new cam::Node(this);
  this->node_data = new dat::Node(this);

  this->node_dynamic = new dyn::Node(this);
  this->node_render = new rnd::Node(this);
  this->node_loader = new ldr::Node(this);

  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf::graph::Profiler* profiler = prf_manager->get_profiler_main();
  this->tasker_main =  profiler->get_or_create_tasker("cpu");

  this->add_node_panel(node_camera);
  this->add_node_panel(node_loader);
  this->add_node_panel(node_data);
  this->add_node_panel(node_render);
  this->add_node_panel(node_dynamic);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_vulkan->init();
  node_data->init();
  node_loader->init();
  node_camera->init();
  node_render->init();

  //---------------------------
}
void Node::loop(){
  tasker_main->task_begin("eng");
  //---------------------------

  node_data->loop();
  node_loader->loop();
  node_camera->loop();
  node_vulkan->loop();
  node_dynamic->loop();

  //---------------------------
  tasker_main->task_end("eng");
}
void Node::gui(){
  //---------------------------

  tasker_main->task_begin("eng::gui");
  node_camera->gui();
  node_data->gui();
  node_loader->gui();
  node_render->gui();
  node_dynamic->gui();
  tasker_main->task_end("eng::gui");

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_data->clean();
  node_loader->clean();
  node_vulkan->clean();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_camera->reset();

  //---------------------------
}
void Node::close(){
  vk::window::GLFW* vk_window = node_vulkan->get_vk_window();
  //---------------------------

  vk_window->close_window();

  //---------------------------
}

}
