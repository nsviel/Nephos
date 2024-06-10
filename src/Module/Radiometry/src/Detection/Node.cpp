#include "Node.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad::detection{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->node_radio = node_radio;
  this->rad_struct = new rad::detection::Structure();
  this->rad_glyph = new rad::detection::glyph::Manager(this);
  this->rad_image_detection = new rad::detection::image::Detection(this);
  this->rad_cloud_detection = new rad::detection::cloud::Detection(this);
  this->dat_selection = node_data->get_dat_selection();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  rad_glyph->create_sphere_glyph();

  //---------------------------
}
void Node::loop(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  //---------------------------

  //Cloud and image detection stuff
  rad_image_detection->start_thread(sensor);
  rad_cloud_detection->start_thread(sensor);

  //---------------------------
}

//Subfunction
void Node::step_sphere_detection(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  //---------------------------

  //Verify that we have a sensor type
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  //Measurement step logic
  int& step = rad_struct->sphere.state_step;
  switch(step){
    case rad::detection::VALIDATION:{
      rad_cloud_detection->validate_bbox(sensor);
      break;
    }
    case rad::detection::PROCESSING:{
      step = rad::detection::VALIDATION;
      break;
    }
  }

  //---------------------------
}
void Node::step_chart_detection(){
  if(rad_struct->sphere.state_step == rad::detection::PROCESSING) return;
  //---------------------------

  rad_struct->chart.state_step = rad::detection::PROCESSING;
  //rad_cloud_detection->validate_bbox(sensor);

  //---------------------------
}

}
