#include "Measure.h"

#include <Radiometry/Calibration/Namespace.h>
#include <Utility/Namespace.h>



namespace rad::cal{

//Constructor / Destructor
Measure::Measure(rad::cal::Node* node_calibration){
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
  //rad_plot->update(*sensor);

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
  //rad_plot->reset();

  //---------------------------
}

//Subfunction
void Measure::init(){
  //---------------------------


  //---------------------------
}


}
