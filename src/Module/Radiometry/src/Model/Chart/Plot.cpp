#include "Plot.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model::chart{

//Constructor / Destructor
Plot::Plot(rad::Node* node_radio, rad::model::chart::Model* rad_model){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_model = rad_model;

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::init(){
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  //I(R)
  plot->IfR.title = "I(R)";
  plot->IfR.highlight = vec2(0, 0);
  plot->IfR.axis_x.resolution = measure->R_resolution;
  plot->IfR.axis_x.min = measure->R_range.x;
  plot->IfR.axis_x.max = measure->R_range.y;
  plot->IfR.axis_x.size = measure->R_size;
  plot->IfR.axis_x.data = vector<float>(measure->R_size, 0.0f);
  plot->IfR.axis_y.data = vector<float>(measure->R_size, 0.0f);

  //I(It)
  plot->IfIt.title = "I(It)";
  plot->IfIt.axis_x.resolution = measure->It_resolution;
  plot->IfIt.axis_x.min = measure->It_range.x;
  plot->IfIt.axis_x.max = measure->It_range.y;
  plot->IfIt.axis_x.size = measure->It_size;
  plot->IfIt.axis_x.data = vector<float>(measure->It_size, 0.0f);
  plot->IfIt.axis_y.data = vector<float>(measure->It_size, 0.0f);

  //I(R, It)
  plot->IfRIt.title = "I(R, It)";
  plot->IfRIt.axis_x.resolution = measure->R_resolution;
  plot->IfRIt.axis_x.min = measure->R_range.x;
  plot->IfRIt.axis_x.max = measure->R_range.y;
  plot->IfRIt.axis_x.size = measure->R_size;
  plot->IfRIt.axis_y.resolution = measure->It_resolution;
  plot->IfRIt.axis_y.min = measure->It_range.x;
  plot->IfRIt.axis_y.max = measure->It_range.y;
  plot->IfRIt.axis_y.size = measure->It_size;
  plot->IfRIt.axis_z.size = measure->size;
  plot->IfRIt.axis_z.min = measure->I_range.x;
  plot->IfRIt.axis_z.max = measure->I_range.y;
  plot->IfRIt.axis_z.data = vector<float>(measure->size, 0.0f);

  //---------------------------
}
void Plot::plot_measure(){
  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  if(measure->data.size() == 0) return;

  // Plot 3D scatter plot
  std::vector<float> x, y, z;
  for(const auto& point : measure->data){
    if(point.x == -1 || point.y > 60) continue;
    x.push_back(point.x);
    y.push_back(point.y);
    z.push_back(std::log(point.z));
  }
  matplotlibcpp::scatter(x, y, z, 1, { {"marker", "."}, {"color", "black"} });
  matplotlibcpp::show();

  //---------------------------
}
void Plot::plot_model(){
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
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

  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  if(measure->data.size() > 0){
    std::vector<float> x_raw, y_raw, z_raw;
    for(const auto& point : measure->data){
      if(point.x == -1 || point.y > 60) continue;
      x_raw.push_back(point.x);
      y_raw.push_back(point.y);
      z_raw.push_back(std::log(point.z));
    }
    matplotlibcpp::scatter(x_raw, y_raw, z_raw, 1, { {"marker", "."}, {"color", "black"} });
    matplotlibcpp::show();
  }

  //---------------------------
}

//Subfunction
void Plot::update_plot_data(){
  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  plot->IfR.axis_x.data.clear();
  plot->IfR.axis_y.data.clear();
  plot->IfR.axis_y.fitting.clear();
  plot->IfIt.axis_x.data.clear();
  plot->IfIt.axis_y.data.clear();
  plot->IfIt.axis_y.fitting.clear();

  //Fill model plot data
  for(int i=0; i<measure->data.size(); i++){
    float& R = measure->data[i].x;
    float& It = measure->data[i].y;
    float& I = measure->data[i].z;
    if(R == -1) continue;

    //I(R)
    if(R > optim->axis_x.bound.x && R < optim->axis_x.bound.y // R inside bounds
      && It > optim->axis_y.current && It < optim->axis_y.current + 5){ //It inside selected It + 5 degrees
      //Raw
      plot->IfR.axis_x.data.push_back(R);
      plot->IfR.axis_y.data.push_back(I);

      //Fitted
      float fit = rad_model->apply_model(R, It);
      plot->IfR.axis_y.fitting.push_back(fit);

      if(R > optim->axis_x.current && R < optim->axis_x.current + 0.05){
        plot->IfR.highlight = vec2(R, I);
      }
    }

    //I(It)
    if(It > optim->axis_y.bound[0] && It < optim->axis_y.bound[1] // It It inside user defined bounds
      && R > optim->axis_x.current && R < optim->axis_x.current + 0.05){ //All data between R current + 0.05m
      //Raw
      plot->IfIt.axis_x.data.push_back(It);
      plot->IfIt.axis_y.data.push_back(I);

      //Fitted
      float fit = rad_model->apply_model(R, It);
      plot->IfIt.axis_y.fitting.push_back(fit);
    }

    //I(R, It)
    plot->IfRIt.axis_z.data[i] = I;
  }

  //---------------------------
}
void Plot::reset_plot_data(){
  rad::model::structure::Optimization* optim = &rad_struct->model.optim;
  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  rad::model::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  //I(R)
  for(int i=0; i<plot->IfR.axis_x.data.size(); i++){
    plot->IfR.axis_x.data[i] = 0;
  }
  for(int i=0; i<plot->IfR.axis_y.data.size(); i++){
    plot->IfR.axis_y.data[i] = 0;
  }

  //I(It)
  for(int i=0; i<plot->IfIt.axis_x.data.size(); i++){
    plot->IfIt.axis_x.data[i] = 0;
  }
  for(int i=0; i<plot->IfIt.axis_y.data.size(); i++){
    plot->IfIt.axis_y.data[i] = 0;
  }

  //I(R, It)
  for(int i=0; i<plot->IfRIt.axis_z.data.size(); i++){
    plot->IfRIt.axis_z.data[i] = 0;
    measure->data[i] = vec3(-1, -1, -1);
  }

  //---------------------------
}




/*void Plot::update_plot_data(){
  rad::model::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  utl::base::Plot* plot = &plot->IfR;
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
