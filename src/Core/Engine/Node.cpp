#include "Node.h"

#include <Application/Node.h>
#include <Vulkan/Namespace.h>
#include <Core/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Camera/Namespace.h>
#include <Renderer/Namespace.h>
#include <IO/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>
#include <Control/Namespace.h>
#include <Data/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->node_camera = new cam::Node(this);
  this->node_control = new ctl::Node(this);
  this->node_interface = new rnd::Node(this);

  //Tasker CPU
  prf::dynamic::Manager* prf_dynamic = node_profiler->get_prf_dynamic();
  this->tasker = prf_dynamic->get_tasker_cpu();

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_data->init();
  node_io->init();
  node_camera->init();
  node_interface->init();
  node_radio->init();
  node_profiler->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_profiler->loop();
  tasker->task_begin("eng::loop");
  node_data->loop();
  node_camera->loop();
  node_dynamic->loop();
  node_radio->loop();
  tasker->task_end("eng::loop");

  tasker->task_begin("eng::vulkan");
  node_vulkan->loop();
  tasker->task_end("eng::vulkan");

  //---------------------------
}
void Node::gui(){
  //---------------------------

  tasker->task_begin("eng::gui");

  node_camera->gui();
  node_data->gui();
  node_io->gui();
  node_interface->gui();
  node_dynamic->gui();
  node_radio->gui();

  tasker->task_end("eng::gui");
  node_profiler->gui();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_data->clean();
  node_io->clean();
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

  node_app->close();

  //---------------------------
}

}
