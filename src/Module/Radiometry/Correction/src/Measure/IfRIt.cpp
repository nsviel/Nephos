#include "IfRIt.h"

#include <Radiometry/Correction/Namespace.h>
#include <Utility/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>
#include <python/matplotlibcpp.h>


namespace rad::cor{

//Constructor / Destructor
IfRIt::IfRIt(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_model = node_correction->get_rad_model();

  //---------------------------
}
IfRIt::~IfRIt(){}

//Main function
void IfRIt::init(){
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  plot.IfRIt.title = "I(R, It)";
  plot.IfRIt.axis_x.resolution = measure.R_resolution;
  plot.IfRIt.axis_x.min = measure.R_range.x;
  plot.IfRIt.axis_x.max = measure.R_range.y;
  plot.IfRIt.axis_x.size = measure.R_size;
  plot.IfRIt.axis_y.resolution = measure.It_resolution;
  plot.IfRIt.axis_y.min = measure.It_range.x;
  plot.IfRIt.axis_y.max = measure.It_range.y;
  plot.IfRIt.axis_y.size = measure.It_size;
  plot.IfRIt.axis_z.size = measure.size;
  plot.IfRIt.axis_z.min = measure.I_range.x;
  plot.IfRIt.axis_z.max = measure.I_range.y;
  plot.IfRIt.axis_z.data = std::vector<float>(measure.size, 0.0f);

  //---------------------------
}
void IfRIt::update(dat::base::Sensor& sensor){
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  //Fill model plot data
  for(int i=0; i<measure.data.size(); i++){
    float& R = measure.data[i].x;
    float& I = measure.data[i].z;

    if(R == -1) continue;

    //I(R, It)
    plot.IfRIt.axis_z.data[i] = I;
  }

  //---------------------------
}
void IfRIt::reset(){
  rad::cor::structure::Measure& measure = rad_struct->measure;
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  for(int i=0; i<plot.IfRIt.axis_z.data.size(); i++){
    plot.IfRIt.axis_z.data[i] = 0;
    measure.data[i] = glm::vec3(-1, -1, -1);
  }

  //---------------------------
}

}
