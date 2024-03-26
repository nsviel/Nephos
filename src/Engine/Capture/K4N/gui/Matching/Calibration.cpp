#include "Calibration.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->utl_plot = new utl::implot::Plot();

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::draw_calibration(k4n::dev::Sensor* sensor){
  float height = ImGui::GetContentRegionAvail().y / 3-3.33;
  //---------------------------

  this->plot_IfR(sensor, height);
  this->plot_IfIt(sensor, height);
  this->plot_IfItR(sensor, height);

  //---------------------------
}

//Subfunction
void Calibration::plot_IfR(k4n::dev::Sensor* sensor, float height){
  //---------------------------

  vector<float>& x = k4n_struct->matching.model.vec_R;
  vector<float>& y = k4n_struct->matching.model.vec_I;

  utl_plot->plot_scatter_2d(x, y, height);

  //---------------------------
}
void Calibration::plot_IfIt(k4n::dev::Sensor* sensor, float height){
  //---------------------------

  vector<float> x;
  vector<float> y;

  for(int i=0; i<100; i++){
    x.push_back(i);
    y.push_back(-i);
  }

  y[50] = 5;

  utl_plot->plot_scatter_2d(x, y, height);

  //---------------------------
}
void Calibration::plot_IfItR(k4n::dev::Sensor* sensor, float height){
  //---------------------------

  vector<float> x;
  vector<float> y;

  for(int i=0; i<100; i++){
    x.push_back(i);
    y.push_back(100);
  }

  y[50] = 5;

  utl_plot->plot_scatter_2d(x, y, height);

  //---------------------------
}

}
