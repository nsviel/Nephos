#include "Normal.h"

#include <Dynamic/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <cstdlib>
#include <chrono>


namespace dyn::cloud{

// Constructor / Destructor
Normal::Normal(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->ope_converter = new ope::image::Converter();
  this->ope_normal = new ope::normal::Structured();
  this->dat_image = node_data->get_dat_image();

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::start_thread(dat::base::Entity* entity){
  //---------------------------

  if(thread.joinable()){
    this->thread.join();
  }
  this->thread = std::thread(&Normal::run_thread, this, entity);

  //---------------------------
}
void Normal::run_thread(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  //Compute normal
  ope_normal->set_knn(dyn_struct->operation.normal.knn);
  ope_normal->compute_normal(data);
  dyn_struct->operation.normal.time = ope_normal->get_time();

  //Make normal image
  utl::media::Image* image = dat_image->get_or_create_image(entity, utl::media::NORMAL);
  ope_converter->convert_normal_to_image(data, image);

  //---------------------------
  this->thread_idle = true;
}
void Normal::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
