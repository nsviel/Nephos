#include "Control.h"

#include <Engine/Engine.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Element/src/Namespace.h>
#include <Utility/Function/Math/fct_math.h>


namespace eng::ope::gui{

//Constructor / Destructor
Control::Control(Engine* engine){
  //---------------------------

  util::Node* utility = engine->get_utility();
  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::cam::Node* node_camera = engine->get_node_camera();

  this->engine = engine;
  this->utl_window = utility->get_utl_window();
  this->cam_manager = node_camera->get_camera_manager();
  this->cam_control = node_camera->get_camera_control();
  this->sce_scene = node_scene->get_scene();
  this->sce_database = node_scene->get_scene_database();
  this->ope_operation = new eng::ope::Operation();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();
  this->control_keyboard_translation();
  this->control_mouse_wheel();

  //---------------------------
}

//Keyboard
void Control::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  utl::type::Set* data_set = sce_database->get_data_set();
  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Tab)){
      utl::type::Set* set_scene = sce_scene->get_set_scene();
      set_scene->select_next_entity();
      break;
    }

    //Suppr key - Delete selected
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
      utl::type::Set* set_scene = sce_scene->get_set_scene();
      set_scene->delete_entity(set_scene->get_selected_entity());
      break;
    }

    //R key - Reset
    if(ImGui::IsKeyPressed(ImGuiKey_R)){
      engine->reset();
      break;
    }
  }

  //----------------------------
}
void Control::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  utl::type::Set* data_set = sce_database->get_data_set();
  for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    if(!io.MouseDown[1]){
      utl::type::Set* set = sce_scene->get_selected_set();

      //Shift speed up
      float translation_qtt = 0.01;
      if(io.KeysDown[340]){
        //translation_qtt = cloud_trans_speed * 5;
      }

      // Z key
      if(io.KeysDown[571]){
        vec3 translation = vec3(translation_qtt, 0, 0);
        ope_operation->make_translation(set, translation);
        break;
      }
      // S key
      if(io.KeysDown[564]){
        vec3 translation = vec3(-translation_qtt, 0, 0);
        ope_operation->make_translation(set, translation);
        break;
      }
      // D key
      if(io.KeysDown[549]){
        vec3 translation = vec3(0, translation_qtt, 0);
        ope_operation->make_translation(set, translation);
        break;
      }
      // Q key
      if(io.KeysDown[562]){
        vec3 translation = vec3(0, -translation_qtt, 0);
        ope_operation->make_translation(set, translation);
        break;
      }
      // A key
      if(io.KeysDown[546]){
        vec3 translation = vec3(0, 0, translation_qtt);
        ope_operation->make_translation(set, translation);
        break;
      }
      // E key
      if(io.KeysDown[550]){
        vec3 translation = vec3(0, 0, -translation_qtt);
        ope_operation->make_translation(set, translation);
        break;
      }
    }
  }

  //----------------------------
}

//Mouse
void Control::control_mouse_wheel(){
  static int wheel_mode = 0;
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    wheel_mode++;
    if(wheel_mode >= 3) wheel_mode = 0;
  }

  //Wheel actions
  if(io.MouseWheel && io.MouseDownDuration[1] == -1){
    //Rotation quantity
    float radian = 5 * M_PI/180 * 50;
    vec3 R;
    if(wheel_mode == 0){
      R = vec3(0, 0, math::sign(io.MouseWheel) * radian);
    }
    else if(wheel_mode == 1){
      R = vec3(0, math::sign(io.MouseWheel) * radian, 0);
    }
    else if(wheel_mode == 2){
      R = vec3(math::sign(io.MouseWheel) * radian, 0, 0);
    }

    //Apply rotation
    utl::type::Set* set = sce_scene->get_selected_set();
    ope_operation->make_rotation(set, R);
  }

  //----------------------------
}

}
