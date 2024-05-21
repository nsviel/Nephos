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
  this->init();
}
Measure::~Measure(){}

//Main function
void Measure::init(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //R
  measure->R_resolution = 0.01f;
  measure->R_range = glm::vec2(0.0f, 5.0f);
  measure->R_size = (measure->R_range.y - measure->R_range.x) / measure->R_resolution + 1;

  //It
  measure->It_resolution = 1.0f;
  measure->It_range = glm::vec2(0.0f, 90.0f);
  measure->It_size = (measure->It_range.y - measure->It_range.x) / measure->It_resolution + 1;

  //I
  measure->I_range = glm::vec2(0.0f, 1500.0f);

  //Measure
  measure->size = measure->R_size * measure->It_size;
  measure->data = vector<vec3>(measure->size, vec3(-1, -1, -1));


  rad_plot->init();

  //---------------------------
}

//Subfunction
void Measure::import_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Import file model data
  measure->data = utl::file::read_vector(measure->path);
  this->find_optimization_bound();
  rad_plot->update_plot_data();

  //---------------------------
}
void Measure::export_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  utl::file::write_vector(measure->path, measure->data);

  //---------------------------
}
void Measure::clear_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Import file model data
  measure->data.clear();
  rad_plot->clear_plot_data();

  //---------------------------
}
void Measure::find_optimization_bound(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  vec2 R_bound = vec2(1000, 0);
  vec2 It_bound = vec2(1000, 0);

  for(int i=0; i<measure->data.size(); i++){
    //R
    float& R = measure->data[i].x;
    if(R < 0) continue;
    if(R < R_bound.x) R_bound.x = R;
    if(R > R_bound.y) R_bound.y = R;

    //It
    float& It = measure->data[i].y;
    if(It < 0) continue;
    if(It < It_bound.x) It_bound.x = It;
    if(It > It_bound.y) It_bound.y = It;
  }

  optim->axis_x.bound = R_bound;
  optim->axis_y.bound = It_bound;
  optim->axis_x.current = (R_bound.x + R_bound.y) / 2;
  optim->axis_y.current = (It_bound.x + It_bound.y) / 2;

  //---------------------------
}

}
