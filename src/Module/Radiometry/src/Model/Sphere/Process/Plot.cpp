#include "Plot.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::model::sphere{

//Constructor / Destructor
Plot::Plot(rad::model::Node* node_model){
  //---------------------------

  this->rad_struct = node_model->get_rad_struct();
  this->model_sphere = node_model->get_model_sphere();

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::init(){
  rad::model::sphere::structure::Optimization* optim = &rad_struct->sphere.optim;
  rad::model::sphere::structure::Sphere* sphere = &rad_struct->sphere.sphere;
  rad::model::sphere::structure::Plot* plot = &rad_struct->sphere.plot;
  //---------------------------

  //I(R)
  plot->IfR.title = "I(R)";
  plot->IfR.highlight = vec2(0, 0);
  plot->IfR.axis_x.resolution = sphere->R_resolution;
  plot->IfR.axis_x.min = sphere->R_range.x;
  plot->IfR.axis_x.max = sphere->R_range.y;
  plot->IfR.axis_x.size = sphere->R_size;
  plot->IfR.axis_x.data = vector<float>(sphere->R_size, 0.0f);
  plot->IfR.axis_y.data = vector<float>(sphere->R_size, 0.0f);

  //I(It)
  plot->IfIt.title = "I(It)";
  plot->IfIt.axis_x.resolution = sphere->It_resolution;
  plot->IfIt.axis_x.min = sphere->It_range.x;
  plot->IfIt.axis_x.max = sphere->It_range.y;
  plot->IfIt.axis_x.size = sphere->It_size;
  plot->IfIt.axis_x.data = vector<float>(sphere->It_size, 0.0f);
  plot->IfIt.axis_y.data = vector<float>(sphere->It_size, 0.0f);

  //I(R, It)
  plot->IfRIt.title = "I(R, It)";
  plot->IfRIt.axis_x.resolution = sphere->R_resolution;
  plot->IfRIt.axis_x.min = sphere->R_range.x;
  plot->IfRIt.axis_x.max = sphere->R_range.y;
  plot->IfRIt.axis_x.size = sphere->R_size;
  plot->IfRIt.axis_y.resolution = sphere->It_resolution;
  plot->IfRIt.axis_y.min = sphere->It_range.x;
  plot->IfRIt.axis_y.max = sphere->It_range.y;
  plot->IfRIt.axis_y.size = sphere->It_size;
  plot->IfRIt.axis_z.size = sphere->size;
  plot->IfRIt.axis_z.min = sphere->I_range.x;
  plot->IfRIt.axis_z.max = sphere->I_range.y;
  plot->IfRIt.axis_z.data = vector<float>(sphere->size, 0.0f);

  //---------------------------
}
void Plot::plot_measure(){
  //---------------------------

  if(rad_struct->sphere.sphere.data.size() == 0) return;

  // Plot 3D scatter plot
  std::vector<float> x, y, z;
  for(const auto& point : rad_struct->sphere.sphere.data){
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
  rad::model::sphere::structure::Optimization* optim = &rad_struct->sphere.optim;
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

  if(rad_struct->sphere.sphere.data.size() > 0){
    std::vector<float> x_raw, y_raw, z_raw;
    for(const auto& point : rad_struct->sphere.sphere.data){
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
  rad::model::sphere::structure::Optimization* optim = &rad_struct->sphere.optim;
  rad::model::sphere::structure::Plot* plot = &rad_struct->sphere.plot;
  //---------------------------

  plot->IfR.axis_x.data.clear();
  plot->IfR.axis_y.data.clear();
  plot->IfR.axis_y.fitting.clear();
  plot->IfIt.axis_x.data.clear();
  plot->IfIt.axis_y.data.clear();
  plot->IfIt.axis_y.fitting.clear();

  //Fill model plot data
  for(int i=0; i<rad_struct->sphere.sphere.data.size(); i++){
    float& R = rad_struct->sphere.sphere.data[i].x;
    float& It = rad_struct->sphere.sphere.data[i].y;
    float& I = rad_struct->sphere.sphere.data[i].z;
    if(R == -1) continue;

    //I(R)
    if(R > optim->axis_x.bound.x && R < optim->axis_x.bound.y // R inside bounds
      && It > optim->axis_y.current && It < optim->axis_y.current + 5){ //It inside selected It + 5 degrees
      //Raw
      plot->IfR.axis_x.data.push_back(R);
      plot->IfR.axis_y.data.push_back(I);

      //Fitted
      float fit = model_sphere->apply_model(R, It);
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
      float fit = model_sphere->apply_model(R, It);
      plot->IfIt.axis_y.fitting.push_back(fit);
    }

    //I(R, It)
    plot->IfRIt.axis_z.data[i] = I;
  }

  //---------------------------
}
void Plot::reset_plot_data(){
  rad::model::sphere::structure::Optimization* optim = &rad_struct->sphere.optim;
  rad::model::sphere::structure::Sphere* sphere = &rad_struct->sphere.sphere;
  rad::model::sphere::structure::Plot* plot = &rad_struct->sphere.plot;
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
    rad_struct->sphere.sphere.data[i] = vec3(-1, -1, -1);
  }

  //---------------------------
}




/*void Plot::update_plot_data(){
  rad::model::sphere::structure::Sphere* sphere = &rad_struct->sphere.sphere;
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