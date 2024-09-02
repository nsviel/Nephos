#include "Graph.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Processing/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n{

//Constructor / Destructor
Graph::Graph(k4n::Node* node_k4n){
  //---------------------------

  dyn::prc::Node* node_processing = node_k4n->get_node_processing();

  this->k4n_image = new k4n::processing::image::Data(node_k4n);
  this->k4n_cloud = new k4n::processing::cloud::Data(node_k4n);
  this->dyn_ope_image = node_processing->get_ope_image();
  this->dyn_ope_cloud = node_processing->get_ope_cloud();

  this->thr_pool = new dat::sensor::Pool(100);

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::init(k4n::base::Sensor& sensor){
  //---------------------------

  sensor.graph.add_task("data", [this](dat::base::Sensor& sensor){ k4n_image->extract_data(sensor); });
  sensor.graph.add_task("cloud", [this](dat::base::Sensor& sensor){ k4n_cloud->extract_data(sensor); });
  sensor.graph.add_task("operation", [this](dat::base::Sensor& sensor){ dyn_ope_cloud->run_operation(sensor); });
  sensor.graph.add_dependency("data", "cloud");
  sensor.graph.add_dependency("cloud", "operation");

  //---------------------------
}
void Graph::run(k4n::base::Sensor& sensor){
  //---------------------------

  sensor.graph.execute(*thr_pool, sensor);

  //---------------------------
}


}
