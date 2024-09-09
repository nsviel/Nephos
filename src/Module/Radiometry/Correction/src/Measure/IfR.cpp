#include "IfR.h"

#include <Radiometry/Correction/Namespace.h>
#include <Utility/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::cor{

//Constructor / Destructor
IfR::IfR(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_model = node_correction->get_rad_model();

  //---------------------------
}
IfR::~IfR(){}

//Main function
void IfR::init(){
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  plot.IfR.title = "I(R)";
  plot.IfR.highlight = glm::vec2(0, 0);
  plot.IfR.axis_x.resolution = measure.R_resolution;
  plot.IfR.axis_x.min = measure.R_range.x;
  plot.IfR.axis_x.max = measure.R_range.y;
  plot.IfR.axis_x.size = measure.R_size;
  plot.IfR.axis_x.data = std::vector<float>(measure.R_size, 0.0f);
  plot.IfR.axis_y.data = std::vector<float>(measure.R_size, 0.0f);

  //---------------------------
}
void IfR::update(dat::base::Sensor& sensor){
  dat::sensor::Model* model = rad_model->get_model(sensor, "NFOV");
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  plot.IfR.axis_x.data.clear();
  plot.IfR.axis_y.data.clear();
  plot.IfR.axis_y.fitting.clear();

  //Fill model plot data
  for(int i=0; i<measure.data.size(); i++){
    float& R = measure.data[i].x;
    float& It = measure.data[i].y;
    float& I = measure.data[i].z;

    if(R == -1) continue;
    if(R < model->axis_x.bound.x || R > model->axis_x.bound.y) return; // R inside bounds
    if(It < model->axis_y.current && It > model->axis_y.current + 5) return; //It inside selected It + 5 degrees

    //Raw data
    plot.IfR.axis_x.data.push_back(R);
    plot.IfR.axis_y.data.push_back(I);

    //Fitted data
    if(rad_model->is_model_build(sensor)){
      float fit = rad_model->apply_model(R, It);
      plot.IfR.axis_y.fitting.push_back(fit);
    }

    if(R > model->axis_x.current && R < model->axis_x.current + 0.05){
      plot.IfR.highlight = glm::vec2(R, I);
    }
  }

  //---------------------------
}
void IfR::reset(){
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  for(int i=0; i<plot.IfR.axis_x.data.size(); i++){
    plot.IfR.axis_x.data[i] = 0;
  }
  for(int i=0; i<plot.IfR.axis_y.data.size(); i++){
    plot.IfR.axis_y.data[i] = 0;
  }

  //---------------------------
}

}
