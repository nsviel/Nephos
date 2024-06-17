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
  this->dat_glyph = node_data->get_dat_glyph();

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(thread.joinable()){
    this->thread.join();
  }
  this->thread = std::thread(&Normal::run_thread, this, sensor);

  //---------------------------
}
void Normal::run_thread(dyn::base::Sensor* sensor){
  utl::base::Data* data = &sensor->data;
  //---------------------------

  //Compute normal
  ope_normal->set_knn(dyn_struct->operation.normal.knn);
  ope_normal->compute_normal(data);
  dyn_struct->operation.normal.time = ope_normal->get_time();

  //Make normal image
  utl::media::Image* image = dat_image->get_or_create_image(sensor, utl::media::NORMAL);
  image->timestamp = sensor->timestamp.current;
  ope_converter->convert_normal_to_image(data, image);

  dat_glyph->update_glyph(sensor, dat::base::object::NORMAL);

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
