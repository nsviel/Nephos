#include "Panel.h"

#include <Engine/Camera/Namespace.h>
#include <imgui/core/imgui.h>


namespace cam::gui{

//Constructor / Destructor
Panel::Panel(cam::Node* node_camera, bool* show_window){
  //---------------------------

  this->cam_control = node_camera->get_cam_control();
  this->cam_manager = node_camera->get_cam_manager();
  this->cam_struct = node_camera->get_cam_struct();
  this->show_window = show_window;
  this->name = "Camera";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, flag) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  //---------------------------

  this->cam_action();
  this->cam_info();
  this->cam_parameter();
  this->cam_pather();

  //---------------------------
}

//Subfunction
void Panel::cam_action(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Screenshot##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    cam_manager->make_screenshot_color();
  }
  if(ImGui::Button("Depth map##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    cam_manager->make_screenshot_depth();
  }
  if(ImGui::Button("Reset pose##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    cam_manager->reset_camera();
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}
void Panel::cam_info(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  ImGui::BeginTable("camera##stats", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 100.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

  //ID
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("ID"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", camera->ID);

  //Pose
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Pose"); ImGui::TableNextColumn();
  switch(camera->mode){
    case CAMERA_MODE_PLAYER:{
      float* floatArray = reinterpret_cast<float*>(&camera->cam_pose);
      ImGui::DragFloat3("##444", floatArray, 0.01f, -100.0f, 100.0f, "%.2f");
      ImGui::SameLine();
      if(ImGui::Button("R")){
        camera->cam_pose = glm::vec3(0, 0, 0);
      }
      break;
    }
    case CAMERA_MODE_ARCBALL:{
      ImGui::TextColored(color, "%.2f   %.2f   %.2f", camera->cam_pose[0], camera->cam_pose[1], camera->cam_pose[2]);
      break;
    }
  }

  //Azimuth
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Azimuth"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f°", camera->angle_azimuth * 180 / M_PI);

  //Elevation
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Elevation"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f°", camera->angle_elevation * 180 / M_PI);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Panel::cam_parameter(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  //Camera parameters
  ImGui::SliderFloat("FOV (°)", &camera->fov, 1.0f, 179.0f);
  glm::vec2* sensibility;
  switch(camera->mode){
    case CAMERA_MODE_PLAYER:{
      sensibility = &camera->player_mouse_sensibility;
      break;
    }
    case CAMERA_MODE_ARCBALL:{
      sensibility = &camera->arcball_mouse_sensibility;
      break;
    }
  }
  ImGui::DragFloatRange2("Sensibility", &sensibility->x, &sensibility->y, 0.01f, 0.01f, 10.0f, "X: %.2f", "Y: %.2f", ImGuiSliderFlags_AlwaysClamp);
  ImGui::DragFloatRange2("Clip", &camera->clip_near, &camera->clip_far, 0.01f, 0.01f, 1000.0f, "Near: %.2f", "Far: %.2f", ImGuiSliderFlags_AlwaysClamp);
  ImGui::Separator();

  //Camera mode
  ImGui::Columns(2);
  ImGui::Text("Projection");
  if(ImGui::RadioButton("Perspective", &camera->projection, CAMERA_PROJ_PERSPECTIVE)){
    cam_control->set_camera_proj(camera, camera->projection);
  }
  if(ImGui::RadioButton("Orthographic", &camera->projection, CAMERA_PROJ_ORTHOGRAPHIC)){
    cam_control->set_camera_proj(camera, camera->projection);
  }

  ImGui::NextColumn();
  ImGui::Text("Mode");
  if(ImGui::RadioButton("Player", &camera->mode, CAMERA_MODE_PLAYER)){
    camera->reset();
    camera->mode = CAMERA_MODE_PLAYER;
    cam_control->set_camera_mode(camera);
  }
  if(ImGui::RadioButton("Arcball", &camera->mode, CAMERA_MODE_ARCBALL)){
    camera->reset();
    camera->mode = CAMERA_MODE_ARCBALL;
    cam_control->set_camera_mode(camera);
  }
  ImGui::Columns(1);

  //---------------------------
  ImGui::Separator();
}
void Panel::cam_pather(){
  //---------------------------

  ImGui::Text("Path");
  ImGui::SameLine();
  ImGui::Checkbox("##path_enable", &cam_struct->path.enable);
  if(cam_struct->path.enable){
    ImGui::SliderFloat("Amplitude", &cam_struct->path.amplitude, 0.0f, 20.0f);
    ImGui::SliderFloat("Frequency", &cam_struct->path.frequency, 0.0f, 10.0f);
    ImGui::SliderFloat("Lambda", &cam_struct->path.lambda, 0.0f, 20.0f);
  }

  //---------------------------
  ImGui::Separator();
}
void Panel::cam_mode(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  if(ImGui::Button(ICON_FA_CAMERA "##camera123")){
    cam_control->set_next_camera_mode();
  }

  //---------------------------
}

}
