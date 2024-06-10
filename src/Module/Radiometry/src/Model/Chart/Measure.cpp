#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model::chart{

//Constructor / Destructor
Measure::Measure(rad::model::Node* node_model){
  //---------------------------

  this->rad_struct = node_model->get_rad_struct();
  //this->rad_plot = node_model->get_rad_plot();

  //---------------------------
  this->init();
}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  //---------------------------

  //Import file model data
  rad_struct->chart.data = utl::file::read_vector(rad_struct->chart.path);
  //rad_plot->update_plot_data();

  //---------------------------
}
void Measure::export_measure(){
  //---------------------------

  utl::file::write_vector(rad_struct->chart.path, rad_struct->chart.data);

  //---------------------------
}
void Measure::clear_measure(){
  //---------------------------

  //Import file model data
  rad_struct->chart.data.clear();
  //rad_plot->reset_plot_data();

  //---------------------------
}

//Subfunction
void Measure::init(){
  //---------------------------


  //---------------------------
}


}
