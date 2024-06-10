#include "Plot.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model::chart{

//Constructor / Destructor
Plot::Plot(rad::Node* node_radio, rad::model::chart::Model* rad_model){
  //---------------------------

  rad::model::Node* node_model = node_radio->get_node_model();

  this->rad_struct = node_model->get_rad_struct();
  this->rad_model = rad_model;

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::init(){
  //---------------------------


  //---------------------------
}
void Plot::plot_measure(){
  //---------------------------


  //---------------------------
}

//Subfunction
void Plot::update_plot_data(){
  //---------------------------


  //---------------------------
}
void Plot::reset_plot_data(){
  //---------------------------


  //---------------------------
}

}
