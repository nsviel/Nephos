#include "Measure.h"

#include <Radiometry/Correction/Namespace.h>
#include <Utility/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::cor::io{

//Constructor / Destructor
Measure::Measure(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_plot = new rad::cor::Plot(node_correction);
  this->rad_measure = node_correction->get_rad_measure();
  this->rad_model = node_correction->get_rad_model();

  //---------------------------

}
Measure::~Measure(){}

//Main function
void Measure::import_measure(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  std::string path = rad_struct->measure.path.build();

  //Determine depth mode

  //Import file model data
  rad_struct->measure.data = utl::file::read_vector(path);

  if(rad_struct->measure.data.size() != 0){
    rad_model->find_model_bound(sensor);
    rad_plot->update_plot_data(sensor);
  }

  //---------------------------
}
void Measure::export_measure(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  std::string path = rad_struct->measure.path.build();
  utl::file::write_vector(path, rad_struct->measure.data);

  //---------------------------
}
void Measure::clear_measure(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  //Import file model data
  rad_struct->measure.data.clear();
  rad_plot->reset_plot_data();

  //---------------------------
}

}
