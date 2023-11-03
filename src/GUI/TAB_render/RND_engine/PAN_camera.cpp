#include "PAN_camera.h"

#include <GUI.h>
#include <Engine.h>
#include <Param.h>
#include <TAB_render/RND_config/RND_panel.h>
#include <ENG_camera/struct_camera.h>


//Constructor / Destructor
PAN_camera::PAN_camera(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  Param* param = engine->get_param();
  this->camera = &param->camera;

  //---------------------------
}
PAN_camera::~PAN_camera(){}

//Main function
void PAN_camera::design_panel(){
  //---------------------------

  this->cam_parameter();
  this->cam_info();

  //---------------------------
}

//Subfunction
void PAN_camera::cam_parameter(){
  //---------------------------

  //Camera parameters
  ImGui::SliderFloat("FOV (°)", &camera->fov, 100.0f, 1.0f);
  ImGui::DragFloat("Speed", &camera->speed_move, 0.01, 0, 20, "%.2f");
  ImGui::DragFloatRange2("Clip", &camera->clip_near, &camera->clip_far, 0.01f, 0.01f, 1000.0f, "%.2f", "%.2f", ImGuiSliderFlags_AlwaysClamp);
  ImGui::Separator();

  //Camera mode
  ImGui::Columns(2);
  static int projection = 0;
  ImGui::Text("Projection");
  if(ImGui::RadioButton("Perspective", &projection, 0)){
    camera->projection = "perspective";
  }
  if(ImGui::RadioButton("Orthographic", &projection, 1)){
    camera->projection = "orthographic";
  }

  ImGui::NextColumn();
  static int mode = 0;
  ImGui::Text("Mode");
  if(ImGui::RadioButton("Default", &mode, 0)){
    camera->mode = "first_person";
  }
  if(ImGui::RadioButton("Arcball", &mode, 1)){
    camera->mode = "arcball";
  }
  ImGui::Columns(1);
  ImGui::Separator();

  //---------------------------
}
void PAN_camera::cam_info(){
  //---------------------------

  //Camera position
  ImGui::Text("Pose");
  vec3* cam_position = &camera->cam_P;
  float* floatArray = &cam_position[0].x;
  if(ImGui::Button("R")){
    camera->cam_P = vec3(0, 0, 0);
  }
  ImGui::SameLine();
  ImGui::DragFloat3("##444", floatArray, 0.01f, -100.0f, 100.0f);

  //Camera angles
  ImGui::Text("Horizontal angle : %.2f°", camera->angle_azimuth * 180 / M_PI);
  ImGui::Text("Vertical angle : %.2f°", camera->angle_elevation * 180 / M_PI);

  //---------------------------
}
