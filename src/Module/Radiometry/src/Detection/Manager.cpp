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
  this->dat_graph = node_data->get_dat_graph();
  this->ope_image = new ope::image::Manager();

  this->sphere_step = rad::detection::NO_DATA;
  this->chart_step = rad::detection::NO_DATA;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::loop(){
  dat::base::Entity* entity = dat_graph->get_selected_entity();
  //---------------------------

  if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
    utl::media::Image* image = ope_image->get_image(sensor, utl::media::INTENSITY);
    if(image != nullptr && image->new_data){
      rad_image_detection->start_thread(sensor, image);
    }


    //rad_cloud_detection->start_thread(sensor, &sensor->ir.image);
  }

  if(rad_struct->model.sphere.has_data) sphere_step = rad::detection::HAS_DATA;
  if(rad_struct->model.chart.has_data) chart_step = rad::detection::HAS_DATA;

  //---------------------------
}

//Subfunction
void Manager::next_sphere_step(){
  //---------------------------

  switch(sphere_step){
    case rad::detection::VALIDATION:{
      //rad_cloud_detection->validate_bbox(sensor);
      break;
    }
    case rad::detection::PROCESSING:{
      this->sphere_step = rad::detection::VALIDATION;
      break;
    }
  }

  //---------------------------
}
void Manager::next_chart_step(){
  //---------------------------

  switch(chart_step){
    case rad::detection::VALIDATION:{
      //rad_cloud_detection->validate_bbox(sensor);
      break;
    }
    case rad::detection::PROCESSING:{
      this->chart_step = rad::detection::VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
