#include "Model.h"

#include <K4N/Namespace.h>
#include <Operation/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_hough = new k4n::utils::Hough();
  this->ope_fitting = new ope::attribut::Fitting();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::detect_sphere(utl::media::Image* utl_image){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  utl::type::Entity* entity = master->selected_entity;
  //---------------------------

  if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
    utl::media::Image* raw_image = &sensor->image.ir;
    vector<vec3> vec_circle = k4n_hough->sphere_detection(raw_image);
    k4n_hough->draw_best_sphere(raw_image, vec_circle, utl_image);
  }

  //---------------------------
}


}
