#include "Plot.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model{

//Constructor / Destructor
Plot::Plot(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::plot_measure(){
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
    matplotlibcpp::scatter(x, y, z, 1, { {"marker", "."}, {"color", "black"} });
    matplotlibcpp::show();
  }

  //---------------------------
}
void Plot::plot_model(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  //---------------------------

  //if(ope_surface->has_been_computed() == false){
    //this->compute_model();
  //}
  /*
  // Generate values for x and y
  std::vector<float> x_values;
  for(float i = optim->axis_x.bound[0]; i <= optim->axis_x.bound[1]; i += optim->axis_x.resolution){
    x_values.push_back(i);
  }

  std::vector<float> y_values;
  for(float i = optim->axis_y.bound[0]; i <= optim->axis_y.bound[1]; i += optim->axis_y.resolution){
    y_values.push_back(i);
  }

  // Compute z values and fill x, y, and z vectors
  std::vector<std::vector<float>> x, y, z;
  for(float x_val : x_values){
    std::vector<float> row_x, row_y, row_z;
    for(float y_val : y_values){
      row_x.push_back(x_val);
      row_y.push_back(y_val);

      float z_value = apply_model(x_val, y_val);
      row_z.push_back(z_value);
    }
    x.push_back(row_x);
    y.push_back(row_y);
    z.push_back(row_z);
  }

  // Ensure z is not empty before plotting
  if (z.size() == 0 || z[0].size() == 0) return;
  matplotlibcpp::plot_surface(x, y, z);
  */

  rad::structure::Measure* measure = &rad_struct->model.measure;
  if(measure->vec_data.size() > 0) {
    std::vector<float> x_raw, y_raw, z_raw;
    for(const auto& point : measure->vec_data){
      if(point.x == -1 || point.y > 60) continue;
      x_raw.push_back(point.x);
      y_raw.push_back(point.y);
      z_raw.push_back(log(point.z));
    }
    matplotlibcpp::scatter(x_raw, y_raw, z_raw, 1, { {"marker", "."}, {"color", "black"} });
    matplotlibcpp::show();
  }

  //---------------------------
}

//Subfunction
void Plot::init_plot_data(){
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
void Plot::update_plot_data(){
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
void Plot::clear_plot_data(){
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




/*void Plot::update_plot_data(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  utl::base::Plot* plot = &measure->IfR;
  for(int i=0; i<plot->axis_x.data.size(); i++){
    float& x = plot->axis_x.data[i];
    float& y = plot->axis_y.data[i];
    float z = apply_model(x, y);
    //plot->axis_x.fitting.push_back();
    //plot->axis_y.fitting = z;
  }



  //---------------------------
}*/

}
