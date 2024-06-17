#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::correction::io{

//Constructor / Destructor
Measure::Measure(rad::correction::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_plot = new rad::correction::Plot(node_correction);
  this->rad_measure = node_correction->get_rad_measure();
  this->rad_model = node_correction->get_rad_model();

  //---------------------------

}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  //---------------------------

  std::string path = rad_struct->measure.get_current_path();

  //Determine depth mode

  //Import file model data
  rad_struct->measure.data = utl::file::read_vector(path);

  if(rad_struct->measure.data.size() != 0){
    rad_model->find_optimization_bound();
    rad_plot->update_plot_data();
  }

  //---------------------------
}
void Measure::export_measure(){
  //---------------------------

  std::string path = rad_struct->measure.get_current_path();
  utl::file::write_vector(path, rad_struct->measure.data);

  //---------------------------
}
void Measure::clear_measure(){
  //---------------------------

  //Import file model data
  rad_struct->measure.data.clear();
  rad_plot->reset_plot_data();

  //---------------------------
}

}
