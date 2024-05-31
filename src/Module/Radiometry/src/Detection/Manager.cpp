#include "Manager.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>


namespace rad::detection{

//Constructor / Destructor
Manager::Manager(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_image_detection = new rad::detection::image::Detection(node_radio);
  this->rad_cloud_detection = new rad::detection::cloud::Detection(node_radio);
  this->dat_selection = node_data->get_dat_selection();
  this->ope_image = new ope::image::Manager();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::loop(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  //---------------------------

  if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
    utl::media::Image* image = ope_image->get_image(sensor, utl::media::INTENSITY);
    if(image != nullptr && image->new_data){
      rad_image_detection->start_thread(sensor, image);
    }


    //rad_cloud_detection->start_thread(sensor, &sensor->ir.image);
  }

  //---------------------------
}

//Subfunction
void Manager::process_sphere_detection(){
  if(rad_struct->model.chart.state_step == rad::detection::PROCESSING) return;
  //---------------------------

  rad_struct->model.sphere.state_step = rad::detection::PROCESSING;
  //rad_cloud_detection->validate_bbox(sensor);

  //---------------------------
}
void Manager::process_chart_detection(){
  if(rad_struct->model.sphere.state_step == rad::detection::PROCESSING) return;
  //---------------------------

  rad_struct->model.chart.state_step = rad::detection::PROCESSING;
  //rad_cloud_detection->validate_bbox(sensor);

  //---------------------------
}

}
