#include "Camera.h"

#include <Engine/Engine.h>



namespace camera::gui{

//Constructor / Destructor
Camera::Camera(Engine* engine, bool* show_window, string name){
  //---------------------------

  camera::src::Node* node_camera = engine->get_node_camera();

  this->cam_control = node_camera->get_camera_control();
  this->cam_manager = node_camera->get_camera_manager();
  this->show_window = show_window;
  this->name = name;

  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Camera::design_panel(){
  //---------------------------

  this->cam_parameter();
  this->cam_info();

  //---------------------------
}

//Subfunction
void Camera::cam_parameter(){
  entity::Camera* camera = cam_manager->get_current_camera();
  //---------------------------

  //Camera parameters
  ImGui::SliderFloat("FOV (°)", &camera->fov, 100.0f, 1.0f);
  if(camera->mode == CAMERA_MODE_PLAYER){
    ImGui::DragFloatRange2("Sensibility", &camera->player_mouse_sensibility.x, &camera->arcball_mouse_sensibility.y, 0.01f, 0.01f, 10.0f, "%.2f", "%.2f", ImGuiSliderFlags_AlwaysClamp);
  }
  if(camera->mode == CAMERA_MODE_ARCBALL){
    ImGui::DragFloatRange2("Sensibility", &camera->arcball_mouse_sensibility.x, &camera->arcball_mouse_sensibility.y, 0.01f, 0.01f, 10.0f, "%.2f", "%.2f", ImGuiSliderFlags_AlwaysClamp);
  }
  ImGui::DragFloatRange2("Clip", &camera->clip_near, &camera->clip_far, 0.01f, 0.01f, 1000.0f, "%.2f", "%.2f", ImGuiSliderFlags_AlwaysClamp);
  ImGui::Separator();

  //Camera mode
  ImGui::Columns(2);
  ImGui::Text("Projection");
  ImGui::RadioButton("Perspective", &camera->projection, CAMERA_PROJ_PERSPECTIVE);
  ImGui::RadioButton("Orthographic", &camera->projection, CAMERA_PROJ_ORTHOGRAPHIC);

  ImGui::NextColumn();
  ImGui::Text("Mode");
  if(ImGui::RadioButton("Player", &camera->mode, CAMERA_MODE_PLAYER)){
    camera->reset_entity();
    camera->mode = CAMERA_MODE_PLAYER;
    cam_control->set_camera_mode();
  }
  if(ImGui::RadioButton("Arcball", &camera->mode, CAMERA_MODE_ARCBALL)){
    camera->reset_entity();
    camera->mode = CAMERA_MODE_ARCBALL;
    cam_control->set_camera_mode();
  }
  ImGui::Columns(1);
  ImGui::Separator();

  //---------------------------
}
void Camera::cam_info(){
  entity::Camera* camera = cam_manager->get_current_camera();
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
  if(ImGui::BeginTable("angle##camera", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 125.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Azimuth"); ImGui::TableNextColumn();
    ImGui::Text("%.2f°", camera->angle_azimuth * 180 / M_PI);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Elevation"); ImGui::TableNextColumn();
    ImGui::Text("%.2f°", camera->angle_elevation * 180 / M_PI);

    ImGui::EndTable();
  }

  //---------------------------
}

}
