#include "Processing.h"

#include <Kinect/Namespace.h>
#include <Core/Namespace.h>
#include <Profiler/Namespace.h>
#include <Processing/Namespace.h>
#include <Thread/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n{

//Constructor / Destructor
Processing::Processing(k4n::Node* node_k4n){
  //---------------------------

  core::Node* node_core = node_k4n->get_node_core();
  dyn::prc::Node* node_processing = node_k4n->get_node_processing();


  this->node_k4n = node_k4n;
  this->thread_pool = node_core->get_thread_pool();
  this->k4n_image = new k4n::processing::image::Data(node_k4n);
  this->k4n_cloud = new k4n::processing::cloud::Data(node_k4n);
  this->dyn_ope_image = node_processing->get_ope_image();
  this->dyn_ope_cloud = node_processing->get_ope_cloud();

  this->thr_pool = new dat::sensor::Pool(100);

  //---------------------------
}
Processing::~Processing(){}

//Main function
void Processing::start_thread(k4n::base::Sensor& sensor){
  //---------------------------

static dat::sensor::Graph graph;
static bool a = false;
if(!a){

  graph.add_task("data", [this](dat::base::Sensor& sensor){ k4n_image->extract_data(sensor); });
  graph.add_task("cloud", [this](dat::base::Sensor& sensor){ k4n_cloud->extract_data(sensor); });
  graph.add_task("operation", [this](dat::base::Sensor& sensor){ dyn_ope_cloud->run_operation(sensor); });
  graph.add_dependency("data", "cloud");
  graph.add_dependency("cloud", "operation");

  a= true;
}

  graph.execute(*thr_pool, sensor);

  //---------------------------
}


}
