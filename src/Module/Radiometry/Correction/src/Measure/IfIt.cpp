#include "IfIt.h"

#include <Radiometry/Correction/Namespace.h>
#include <Utility/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>



namespace rad::cor{

//Constructor / Destructor
IfIt::IfIt(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_model = node_correction->get_rad_model();

  //---------------------------
}
IfIt::~IfIt(){}

//Main function
void IfIt::init(){
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  plot.IfIt.title = "I(It)";
  plot.IfIt.axis_x.resolution = measure.It_resolution;
  plot.IfIt.axis_x.min = measure.It_range.x;
  plot.IfIt.axis_x.max = measure.It_range.y;
  plot.IfIt.axis_x.size = measure.It_size;
  plot.IfIt.axis_x.data = std::vector<float>(measure.It_size, 0.0f);
  plot.IfIt.axis_y.data = std::vector<float>(measure.It_size, 0.0f);

  //---------------------------
}
void IfIt::update(dat::base::Sensor& sensor){
  dat::sensor::Model* model = rad_model->get_model(sensor, "NFOV");
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  plot.IfIt.axis_x.data.clear();
  plot.IfIt.axis_y.data.clear();
  plot.IfIt.axis_y.fitting.clear();

  //Fill model plot data
  for(int i=0; i<measure.data.size(); i++){
    float& R = measure.data[i].x;
    float& It = measure.data[i].y;
    float& I = measure.data[i].z;

    if(R == -1) continue;
    if(It < model->axis_y.bound[0] || It > model->axis_y.bound[1]) return; // It inside user defined bounds
    if(R < model->axis_x.current && R > model->axis_x.current + 0.05) return; //R inside R current + 0.05m

    //Raw data
    plot.IfIt.axis_x.data.push_back(It);
    plot.IfIt.axis_y.data.push_back(I);

    //Fitted data
    if(rad_model->is_model_build(sensor)){
      float fit = rad_model->apply_model(R, It);
      plot.IfIt.axis_y.fitting.push_back(fit);
    }
  }

  //---------------------------
}
void IfIt::reset(){
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  for(int i=0; i<plot.IfIt.axis_x.data.size(); i++){
    plot.IfIt.axis_x.data[i] = 0;
  }
  for(int i=0; i<plot.IfIt.axis_y.data.size(); i++){
    plot.IfIt.axis_y.data[i] = 0;
  }

  //---------------------------
}

}
