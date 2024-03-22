#include "Matching.h"

#include <K4N/Namespace.h>
#include <Render/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Matching::Matching(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();

  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_model = node_k4n->get_k4n_model();
  this->k4n_hough = new k4n::detection::Hough(node_k4n);
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->utl_plot = new utl::implot::Plot();
  this->stream = new eng::render::gui::Stream(node_engine);
  this->gui_detection = new k4n::gui::Detection(node_k4n);

  this->show_window = show_window;
  this->name = "Matching";

  //---------------------------
}
Matching::~Matching(){}

//Main function
void Matching::run_panel(){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  if(*show_window && master != nullptr){
    k4n_struct->matching.panel_open = true;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(master);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }else{
    k4n_struct->matching.panel_open = false;
  }

  //---------------------------
}
void Matching::design_panel(k4n::dev::Master* master){
  k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(master->selected_entity);
  //---------------------------

  this->model_parameter(sensor);
  gui_detection->draw_detection(sensor);
  this->plot_IfR(sensor);

  //---------------------------
}

//Subfunction
void Matching::model_parameter(k4n::dev::Sensor* sensor){
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
void Matching::plot_IfR(k4n::dev::Sensor* sensor){
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
