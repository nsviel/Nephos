#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model::chart{

//Constructor / Destructor
Measure::Measure(rad::Node* node_radio, rad::model::chart::Plot* rad_plot){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_plot = rad_plot;

  //---------------------------
  this->init();
}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  rad::model::structure::Chart* chart = &rad_struct->model.chart;
  //---------------------------

  //Import file model data
  chart->data = utl::file::read_vector(chart->path);
  rad_plot->update_plot_data();

  //---------------------------
}
void Measure::export_measure(){
  rad::model::structure::Chart* chart = &rad_struct->model.chart;
  //---------------------------

  utl::file::write_vector(chart->path, chart->data);

  //---------------------------
}
void Measure::clear_measure(){
  rad::model::structure::Chart* chart = &rad_struct->model.chart;
  //---------------------------

  //Import file model data
  chart->data.clear();
  rad_plot->reset_plot_data();

  //---------------------------
}

//Subfunction
void Measure::init(){
  //---------------------------


  //---------------------------
}


}
