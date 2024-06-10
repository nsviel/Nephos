#include "Measure.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model::sphere{

//Constructor / Destructor
Measure::Measure(rad::Node* node_radio, rad::model::sphere::Plot* rad_plot){
  //---------------------------

  rad::model::Node* node_model = node_radio->get_node_model();

  this->rad_struct = node_model->get_rad_struct();
  this->rad_plot = rad_plot;

  //---------------------------
  this->init();
}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  //---------------------------

  //Import file model data
  rad_struct->sphere.data = utl::file::read_vector(rad_struct->sphere.path);

  if(rad_struct->sphere.data.size() != 0){
    this->find_optimization_bound();
    rad_plot->update_plot_data();
  }

  //---------------------------
}
void Measure::export_measure(){
  //---------------------------

  utl::file::write_vector(rad_struct->sphere.path, rad_struct->sphere.data);

  //---------------------------
}
void Measure::clear_measure(){
  //---------------------------

  //Import file model data
  rad_struct->sphere.data.clear();
  rad_plot->reset_plot_data();

  //---------------------------
}

//Subfunction
void Measure::init(){
  rad::model::structure::Sphere* sphere = &rad_struct->sphere;
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
  //---------------------------

  vec2 R_bound = vec2(1000, 0);
  vec2 It_bound = vec2(1000, 0);

  for(int i=0; i<rad_struct->sphere.data.size(); i++){
    //R
    float& R = rad_struct->sphere.data[i].x;
    if(R < 0) continue;
    if(R < R_bound.x) R_bound.x = R;
    if(R > R_bound.y) R_bound.y = R;

    //It
    float& It = rad_struct->sphere.data[i].y;
    if(It < 0) continue;
    if(It < It_bound.x) It_bound.x = It;
    if(It > It_bound.y) It_bound.y = It;
  }

  rad_struct->optim.axis_x.bound = R_bound;
  rad_struct->optim.axis_y.bound = It_bound;
  rad_struct->optim.axis_x.current = (R_bound.x + R_bound.y) / 2;
  rad_struct->optim.axis_y.current = (It_bound.x + It_bound.y) / 2;

  //---------------------------
}

}
