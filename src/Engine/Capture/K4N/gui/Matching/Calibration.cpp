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
  //---------------------------

  this->model_parameter(sensor);
  this->plot_IfR(sensor);

  //---------------------------
}

//Subfunction
void Calibration::model_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model parameter");

  //Matching sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Sphere diameter", &sensor->detection.sphere_diameter, 0.001, 0.5f, "%.3f m");

  //Matching sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Bounding box factor", &k4n_struct->matching.bbox.scale, 1.0f, 10.0f, "%.2fx");

  //Pixel diviser
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Pixel diviser", &sensor->master->operation.intensity_diviser, 1, 5000);

  //---------------------------
  ImGui::Separator();
}
void Calibration::plot_IfR(k4n::dev::Sensor* sensor){
  //---------------------------

  vector<float> x;
  vector<float> y;

  for(int i=0; i<100; i++){
    x.push_back(i);
    y.push_back(i+1);
  }

  y[50] = 5;

  utl_plot->plot_scatter_2d(x, y);

  //---------------------------
}

}
