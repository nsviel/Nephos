#include "Importer.h"

#include <Core/Namespace.h>
#include <Kinect/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Importer::Importer(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dyn::prc::Node* node_processing = node_k4n->get_node_processing();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->node_k4n = node_k4n;
  this->dat_graph = node_graph->get_gph_graph();
  this->dat_set = node_element->get_dat_set();
  this->dat_sensor = node_element->get_dat_sensor();
  this->k4n_config = new k4n::playback::Configuration(node_k4n);

  this->format = ".mkv";
  this->require_discrete_gpu = true;

  //---------------------------
}
Importer::~Importer(){}

//Main function
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  if(!utl::file::is_exist(path.build())) return nullptr;
  //---------------------------

  //Create sensor
  std::shared_ptr<k4n::playback::Sensor> sensor = std::make_shared<k4n::playback::Sensor>(node_k4n, path);
  this->manage_set_parent(*sensor);
  sensor->start();

  //---------------------------
  return sensor;
}

//Subfunction
void Importer::manage_set_parent(k4n::playback::Sensor& sensor){
  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  //---------------------------

  //Check if already existing
  std::shared_ptr<dat::base::Set> set = dat_set->get_subset(set_graph, "kinect");

  //If not, create it
  if(!set){
    set = std::make_shared<dat::base::Set>();
    set->name = "kinect";
    set->icon = ICON_FA_USER;
    set->is_locked = false;
    set->is_suppressible = true;
    dat_set->add_subset(set_graph, set);
  }

  //Assign to sensor
  sensor->set_parent = set;

  //---------------------------
}

}
