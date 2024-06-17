#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::calibration{

//Constructor / Destructor
Measure::Measure(rad::calibration::Node* node_calibration){
  //---------------------------

  this->rad_struct = node_calibration->get_rad_struct();
  //this->rad_plot = node_calibration->get_rad_plot();

  //---------------------------
  this->init();
}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  //---------------------------

  //std::string path = rad_struct->get_current_path();

  //Import file model data
  //rad_struct->chart.data = utl::file::read_vector(path);
  //rad_plot->update_plot_data();

  //---------------------------
}
void Measure::export_measure(){
  //---------------------------

  //std::string path = rad_struct->get_current_path();

  //utl::file::write_vector(path, rad_struct->chart.data);

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
