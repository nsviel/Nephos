#include "Measure.h"

#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model{

//Constructor / Destructor
Measure::Measure(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();

  //---------------------------
  this->init_plot_data();
}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //Import file model data
  measure->vec_data = utl::file::read_vector(measure->path);
  this->find_measure_bound();
  this->update_plot_data();

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
  this->clear_plot_data();

  //---------------------------
}
void Measure::plot_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  // Plot 3D scatter plot
  if(measure->vec_data.size() > 0) {
    std::vector<float> x, y, z;
    for(const auto& point : measure->vec_data){
      if(point.x == -1 || point.y > 60) continue;
      x.push_back(point.x);
      y.push_back(point.y);
      z.push_back(log(point.z));
    }
    matplotlibcpp::scatter(x, y, z, 0.1, /*keywords=*/{ {"cmap", "viridis"}, {"marker", "."} });
    matplotlibcpp::show();
  }

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

//Plot function
void Measure::init_plot_data(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //I(R)
  measure->IfR.title = "I(R)";
  measure->IfR.highlight = vec2(0, 0);
  measure->IfR.axis_x.resolution = 0.01f;
  measure->IfR.axis_x.min = 0.0f;
  measure->IfR.axis_x.max = 5.0f;
  measure->IfR.axis_x.size = static_cast<int>((measure->IfR.axis_x.max - measure->IfR.axis_x.min) / measure->IfR.axis_x.resolution) + 1;
  measure->IfR.axis_x.data = vector<float>(measure->IfR.axis_x.size, 0.0f);
  measure->IfR.axis_y.data = vector<float>(measure->IfR.axis_x.size, 0.0f);

  //I(It)
  measure->IfIt.title = "I(It)";
  measure->IfIt.axis_x.resolution = 1.0f;
  measure->IfIt.axis_x.min = 0.0f;
  measure->IfIt.axis_x.max = 90.0f;
  measure->IfIt.axis_x.size = static_cast<int>((measure->IfIt.axis_x.max - measure->IfIt.axis_x.min) / measure->IfIt.axis_x.resolution) + 1;
  measure->IfIt.axis_x.data = vector<float>(measure->IfIt.axis_x.size, 0.0f);
  measure->IfIt.axis_y.data = vector<float>(measure->IfIt.axis_x.size, 0.0f);

  //I(R, It)
  measure->IfRIt.title = "I(R, It)";
  measure->IfRIt.axis_x.resolution = 0.01f;
  measure->IfRIt.axis_x.min = 0.0f;
  measure->IfRIt.axis_x.max = 5.0f;
  measure->IfRIt.axis_x.size = static_cast<int>((measure->IfRIt.axis_x.max - measure->IfRIt.axis_x.min) / measure->IfRIt.axis_x.resolution) + 1;
  measure->IfRIt.axis_y.resolution = 1.0f;
  measure->IfRIt.axis_y.min = 0.0f;
  measure->IfRIt.axis_y.max = 90.0f;
  measure->IfRIt.axis_y.size = static_cast<int>((measure->IfRIt.axis_y.max - measure->IfRIt.axis_y.min) / measure->IfRIt.axis_y.resolution) + 1;
  measure->IfRIt.axis_z.min = 0.0f;
  measure->IfRIt.axis_z.max = 2500.0f;
  measure->IfRIt.axis_z.size = measure->IfRIt.axis_x.size * measure->IfRIt.axis_y.size;
  measure->IfRIt.axis_z.data = vector<float>(measure->IfRIt.axis_z.size, 0.0f);

  //Measure
  measure->vec_data = vector<vec3>(measure->IfRIt.axis_z.size, vec3(-1, -1, -1));
  optim->axis_x.bound = vec2(1000, -1);
  optim->axis_x.current = 1;
  optim->axis_y.bound = vec2(0, 90);
  optim->axis_y.current = 40;

  //---------------------------
}
void Measure::update_plot_data(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  //---------------------------

  //Fill model plot data
  for(int i=0; i<measure->vec_data.size(); i++){
    float& R = measure->vec_data[i].x;
    float& It = measure->vec_data[i].y;
    float& I = measure->vec_data[i].z;
    if(R == -1) continue;

    //I(R)
    if(R > optim->axis_x.bound[0] && R < optim->axis_x.bound[1]) // R inside user defined bounds
    if(It > optim->axis_y.current && It < optim->axis_y.current + 5){ //All data between It current + 5 degrees
      int index = static_cast<int>(std::round(R / measure->IfR.axis_x.resolution));
      measure->IfR.axis_x.data[index] = R;
      measure->IfR.axis_y.data[index] = I;

      if(R > optim->axis_x.current && R < optim->axis_x.current + 0.05){
        measure->IfR.highlight = vec2(R, I);
      }
    }

    //I(It)
    if(It > optim->axis_y.bound[0] && It < optim->axis_y.bound[1]) // It It inside user defined bounds
    if(R > optim->axis_x.current && R < optim->axis_x.current + 0.05){ //All data between R current + 0.05m
      int index = static_cast<int>(std::round(It / measure->IfIt.axis_x.resolution));
      measure->IfIt.axis_x.data[index] = It;
      measure->IfIt.axis_y.data[index] = I;
    }

    //I(R, It)
    measure->IfRIt.axis_z.data[i] = I;
  }

  //---------------------------
}
void Measure::clear_plot_data(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  //I(R)
  for(int i=0; i<measure->IfR.axis_x.data.size(); i++){
    measure->IfR.axis_x.data[i] = 0;
  }
  for(int i=0; i<measure->IfR.axis_y.data.size(); i++){
    measure->IfR.axis_y.data[i] = 0;
  }

  //I(It)
  for(int i=0; i<measure->IfIt.axis_x.data.size(); i++){
    measure->IfIt.axis_x.data[i] = 0;
  }
  for(int i=0; i<measure->IfIt.axis_y.data.size(); i++){
    measure->IfIt.axis_y.data[i] = 0;
  }

  //I(R, It)
  for(int i=0; i<measure->IfRIt.axis_z.data.size(); i++){
    measure->IfRIt.axis_z.data[i] = 0;
    measure->vec_data[i] = vec3(-1, -1, -1);
  }

  //---------------------------
}

}
