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
#include <Radiometry/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->app_running = node_app->get_app_running();
  this->node_vulkan = new vk::Node(app_running);
  this->node_profiler = new prf::Node(this);
  this->node_camera = new cam::Node(this);
  this->node_data = new dat::Node(this);
  this->node_radio = new rad::Node(this);
  this->node_dynamic = new dyn::Node(this);
  this->node_render = new rnd::Node(this);
  this->node_loader = new ldr::Node(this);
  this->thread_pool = new utl::thread::Pool(50);

  this->add_node_panel(node_camera);
  this->add_node_panel(node_loader);
  this->add_node_panel(node_data);
  this->add_node_panel(node_render);
  this->add_node_panel(node_dynamic);
  this->add_node_panel(node_radio);

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
  node_radio->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_profiler->loop();
  tasker_main->task_begin("eng");

  node_data->loop();
  node_loader->loop();
  node_camera->loop();
  node_vulkan->loop();
  node_dynamic->loop();
  node_radio->loop();

  tasker_main->task_end("eng");

  //---------------------------
}
void Node::gui(){
  //---------------------------

  tasker_main->task_begin("eng::gui");

  node_camera->gui();
  node_data->gui();
  node_loader->gui();
  node_render->gui();
  node_dynamic->gui();
  node_radio->gui();

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
  node_data->reset();
  node_dynamic->reset();

  //---------------------------
}
void Node::close(){
  //---------------------------

  *app_running = false;

  //---------------------------
}

}
