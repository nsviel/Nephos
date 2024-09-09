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
  this->plot_IfR = new rad::cor::IfR(node_correction);
  this->plot_IfIt = new rad::cor::IfIt(node_correction);
  this->plot_IfRIt = new rad::cor::IfRIt(node_correction);

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::init(){
  //---------------------------

  plot_IfR->init();
  plot_IfIt->init();
  plot_IfRIt->init();

  //---------------------------
}
void Plot::update(dat::base::Sensor& sensor){
  //---------------------------

  plot_IfR->update(sensor);
  plot_IfIt->update(sensor);
  plot_IfRIt->update(sensor);

  //---------------------------
}
void Plot::reset(){
  //---------------------------

  plot_IfR->reset();
  plot_IfIt->reset();
  plot_IfRIt->reset();

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

}
