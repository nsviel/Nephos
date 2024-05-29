#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model::sphere{

//Constructor / Destructor
Measure::Measure(rad::Node* node_radio, rad::model::sphere::Plot* rad_plot){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_plot = rad_plot;

  //---------------------------
  this->init();
}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  rad::model::structure::Sphere* sphere = &rad_struct->model.sphere;
  //---------------------------

  //Import file model data
  sphere->data = utl::file::read_vector(sphere->path);
  this->find_optimization_bound();
  rad_plot->update_plot_data();

  //---------------------------
}
void Measure::export_measure(){
  rad::model::structure::Sphere* sphere = &rad_struct->model.sphere;
  //---------------------------

  utl::file::write_vector(sphere->path, sphere->data);

  //---------------------------
}
void Measure::clear_measure(){
  rad::model::structure::Sphere* sphere = &rad_struct->model.sphere;
  //---------------------------

  //Import file model data
  sphere->data.clear();
  rad_plot->reset_plot_data();

  //---------------------------
}

//Subfunction
void Measure::init(){
  rad::model::structure::Sphere* sphere = &rad_struct->model.sphere;
  //---------------------------

  //R
  sphere->R_resolution = 0.01f;
  sphere->R_range = glm::vec2(0.0f, 5.0f);
  sphere->R_size = (sphere->R_range.y - sphere->R_range.x) / sphere->R_resolution + 1;

  //It
  sphere->It_resolution = 1.0f;
  sphere->It_range = glm::vec2(0.0f, 90.0f);
  sphere->It_size = (sphere->It_range.y - sphere->It_range.x) / sphere->It_resolution + 1;

  //I
  sphere->I_range = glm::vec2(0.0f, 1500.0f);

  //Measure
  sphere->size = sphere->R_size * sphere->It_size;
  sphere->data = vector<vec3>(sphere->size, vec3(-1, -1, -1));


  rad_plot->init();

  //---------------------------
}
void Measure::find_optimization_bound(){
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
  rad::model::structure::Sphere* sphere = &rad_struct->model.sphere;
  //---------------------------

  vec2 R_bound = vec2(1000, 0);
  vec2 It_bound = vec2(1000, 0);

  for(int i=0; i<sphere->data.size(); i++){
    //R
    float& R = sphere->data[i].x;
    if(R < 0) continue;
    if(R < R_bound.x) R_bound.x = R;
    if(R > R_bound.y) R_bound.y = R;

    //It
    float& It = sphere->data[i].y;
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
