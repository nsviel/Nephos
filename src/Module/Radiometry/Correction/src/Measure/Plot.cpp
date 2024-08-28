#include "Plot.h"

#include <Radiometry/Correction/Namespace.h>
#include <Utility/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::cor{

//Constructor / Destructor
Plot::Plot(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_model = node_correction->get_rad_model();

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::init(){
  rad::cor::structure::Measure* sphere = &rad_struct->measure;
  rad::cor::structure::Plot* plot = &rad_struct->plot;
  //---------------------------

  //I(R)
  plot->IfR.title = "I(R)";
  plot->IfR.highlight = glm::vec2(0, 0);
  plot->IfR.axis_x.resolution = sphere->R_resolution;
  plot->IfR.axis_x.min = sphere->R_range.x;
  plot->IfR.axis_x.max = sphere->R_range.y;
  plot->IfR.axis_x.size = sphere->R_size;
  plot->IfR.axis_x.data = std::vector<float>(sphere->R_size, 0.0f);
  plot->IfR.axis_y.data = std::vector<float>(sphere->R_size, 0.0f);

  //I(It)
  plot->IfIt.title = "I(It)";
  plot->IfIt.axis_x.resolution = sphere->It_resolution;
  plot->IfIt.axis_x.min = sphere->It_range.x;
  plot->IfIt.axis_x.max = sphere->It_range.y;
  plot->IfIt.axis_x.size = sphere->It_size;
  plot->IfIt.axis_x.data = std::vector<float>(sphere->It_size, 0.0f);
  plot->IfIt.axis_y.data = std::vector<float>(sphere->It_size, 0.0f);

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
  plot->IfRIt.axis_z.data = std::vector<float>(sphere->size, 0.0f);

  //---------------------------
}

//Subfunction
void Plot::plot_measure(){
  //---------------------------

  if(rad_struct->measure.data.size() == 0) return;

  // Plot 3D scatter plot
  std::vector<float> x, y, z;
  for(const auto& point : rad_struct->measure.data){
    if(point.x == -1 || point.y > 60) continue;
    x.push_back(point.x);
    y.push_back(point.y);
    z.push_back(std::log(point.z));
  }
  matplotlibcpp::scatter(x, y, z, 1, { {"marker", "."}, {"color", "black"} });
  matplotlibcpp::show();

  //---------------------------
}
void Plot::update_plot_data(std::shared_ptr<dat::base::Sensor> sensor){
  dat::base::sensor::Model* model = rad_model->get_model(sensor, "NFOV");
  rad::cor::structure::Plot* plot = &rad_struct->plot;
  //---------------------------

  plot->IfR.axis_x.data.clear();
  plot->IfR.axis_y.data.clear();
  plot->IfR.axis_y.fitting.clear();
  plot->IfIt.axis_x.data.clear();
  plot->IfIt.axis_y.data.clear();
  plot->IfIt.axis_y.fitting.clear();

  //Fill model plot data
  for(int i=0; i<rad_struct->measure.data.size(); i++){
    float& R = rad_struct->measure.data[i].x;
    float& It = rad_struct->measure.data[i].y;
    float& I = rad_struct->measure.data[i].z;
    if(R == -1) continue;

    //I(R)
    if(R > model->axis_x.bound.x && R < model->axis_x.bound.y // R inside bounds
      && It > model->axis_y.current && It < model->axis_y.current + 5){ //It inside selected It + 5 degrees
      //Raw
      plot->IfR.axis_x.data.push_back(R);
      plot->IfR.axis_y.data.push_back(I);

      //Fitted
      if(rad_model->is_model_build(sensor)){
        float fit = rad_model->apply_model(R, It);
        plot->IfR.axis_y.fitting.push_back(fit);
      }

      if(R > model->axis_x.current && R < model->axis_x.current + 0.05){
        plot->IfR.highlight = glm::vec2(R, I);
      }
    }

    //I(It)
    if(It > model->axis_y.bound[0] && It < model->axis_y.bound[1] // It It inside user defined bounds
      && R > model->axis_x.current && R < model->axis_x.current + 0.05){ //All data between R current + 0.05m
      //Raw
      plot->IfIt.axis_x.data.push_back(It);
      plot->IfIt.axis_y.data.push_back(I);

      //Fitted
      if(rad_model->is_model_build(sensor)){
        float fit = rad_model->apply_model(R, It);
        plot->IfIt.axis_y.fitting.push_back(fit);
      }
    }

    //I(R, It)
    plot->IfRIt.axis_z.data[i] = I;
  }

  //---------------------------
}
void Plot::reset_plot_data(){
  rad::cor::structure::Measure* sphere = &rad_struct->measure;
  rad::cor::structure::Plot* plot = &rad_struct->plot;
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
    rad_struct->measure.data[i] = glm::vec3(-1, -1, -1);
  }

  //---------------------------
}




/*void Plot::update_plot_data(){
  rad::cor::structure::Measure* sphere = &rad_struct->measure;
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
