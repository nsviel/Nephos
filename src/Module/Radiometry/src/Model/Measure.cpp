#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model{

//Constructor / Destructor
Measure::Measure(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_plot = node_radio->get_model_plot();

  //---------------------------
  rad_plot->init_plot_data();
}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Import file model data
  measure->vec_data = utl::file::read_vector(measure->path);
  this->find_measure_bound();
  rad_plot->update_plot_data();

  //---------------------------
}
void Measure::export_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  utl::file::write_vector(measure->path, measure->vec_data);

  //---------------------------
}
void Measure::clear_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Import file model data
  measure->vec_data.clear();
  rad_plot->clear_plot_data();

  //---------------------------
}

//Subfunction
void Measure::find_measure_bound(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  for(int i=0; i<measure->vec_data.size(); i++){
    float& R = measure->vec_data[i].x;
    if(R < 0) continue;
    if(R < optim->axis_x.bound[0]) optim->axis_x.bound[0] = R;
    if(R > optim->axis_x.bound[1]) optim->axis_x.bound[1] = R;

    float& It = measure->vec_data[i].y;
    if(It < 0) continue;
    if(It < optim->axis_y.bound[0]) optim->axis_y.bound[0] = It;
    if(It > optim->axis_y.bound[1]) optim->axis_y.bound[1] = It;
  }

  //---------------------------
}

}
