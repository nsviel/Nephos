#include "Control.h"

#include <GUI.h>
#include <Engine/Engine.h>
#include <Engine/Scene/Data/Scene.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Window.h>
#include <Utility/Function/Math/fct_math.h>



namespace gui::engine{

//Constructor / Destructor
Control::Control(GUI* gui){
  //---------------------------

  util::Node* utility = gui->get_utility();
  Engine* engine = gui->get_engine();
  eng::scene::Node* node_scene = engine->get_node_scene();

  this->engine = gui->get_engine();
  this->utl_window = utility->get_utl_window();
  this->camera = engine->get_camera();
  this->node_camera = engine->get_node_camera();
  this->cam_control = node_camera->get_camera_control();
  this->sce_scene = node_scene->get_scene();
  this->sce_database = node_scene->get_scene_database();
  this->sce_operation = new eng::scene::Operation(node_scene);

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(ImVec2 center){
  //---------------------------

  this->control_keyboard_oneAction();
  this->control_keyboard_camMove();
  this->control_keyboard_translation();
  this->control_mouse(center);
  this->control_mouse_wheel();

  //---------------------------
}

//Keyboard
void Control::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  eng::data::Set* data_set = sce_database->get_data_set();
  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Tab)){
      eng::data::Set* set_scene = data_set->get_set("Scene");
      set_scene->select_next_entity();
      break;
    }

    //Suppr key - Delete selected
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
      eng::data::Set* set_scene = data_set->get_set("Scene");
      sce_scene->delete_entity(set_scene->selected_entity);
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
void Control::control_keyboard_camMove(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    if(io.MouseDown[1]){

      //Shift speed up
      bool is_fast = false;
      if(io.KeysDown[340]){
        is_fast = true;
      }

      //Z key or Up key
      if(io.KeysDown[571] || io.KeysDown[515]){
        cam_control->control_keyboard(CAMERA_FORWARD, is_fast);
      }

      //S key or Down key
      if(io.KeysDown[564] || io.KeysDown[516]){
        cam_control->control_keyboard(CAMERA_BACKWARD, is_fast);
      }

      //Q key or Left key
      if(io.KeysDown[562] || io.KeysDown[513]){
        cam_control->control_keyboard(CAMERA_LEFT, is_fast);
      }

      //D key or Left key
      if(io.KeysDown[549] || io.KeysDown[514]){
        cam_control->control_keyboard(CAMERA_RIGHT, is_fast);
      }

      //A key
      if(io.KeysDown[546]){
        cam_control->control_keyboard(CAMERA_DOWN, is_fast);
      }

      //E key
      if(io.KeysDown[550]){
        cam_control->control_keyboard(CAMERA_UP, is_fast);
      }
    }
  }

  //---------------------------
}
void Control::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  eng::data::Set* data_set = sce_database->get_data_set();
  for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    if(!io.MouseDown[1]){
      float translation_qtt = 0.01;

      //Shift speed up
      if(io.KeysDown[340]){
        //translation_qtt = cloud_trans_speed * 5;
      }

      // Z key
      if(io.KeysDown[571]){
        vec3 translation = vec3(translation_qtt, 0, 0);
        eng::data::Entity* entity = sce_scene->get_selected_entity();
        sce_operation->make_translation(entity, translation);
        break;
      }
      // S key
      if(io.KeysDown[564]){
        vec3 translation = vec3(-translation_qtt, 0, 0);
        eng::data::Entity* entity = sce_scene->get_selected_entity();
        sce_operation->make_translation(entity, translation);
        break;
      }
      // D key
      if(io.KeysDown[549]){
        vec3 translation = vec3(0, translation_qtt, 0);
        eng::data::Entity* entity = sce_scene->get_selected_entity();
        sce_operation->make_translation(entity, translation);
        break;
      }
      // Q key
      if(io.KeysDown[562]){
        vec3 translation = vec3(0, -translation_qtt, 0);
        eng::data::Entity* entity = sce_scene->get_selected_entity();
        sce_operation->make_translation(entity, translation);
        break;
      }
      // A key
      if(io.KeysDown[546]){
        vec3 translation = vec3(0, 0, translation_qtt);
        eng::data::Entity* entity = sce_scene->get_selected_entity();
        sce_operation->make_translation(entity, translation);
        break;
      }
      // E key
      if(io.KeysDown[550]){
        vec3 translation = vec3(0, 0, -translation_qtt);
        eng::data::Entity* entity = sce_scene->get_selected_entity();
        sce_operation->make_translation(entity, translation);
        break;
      }
    }
  }

  //----------------------------
}

//Mouse
void Control::control_mouse(ImVec2 center){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  utl_window->set_window_center(vec2(center.x, center.y));

  //Right click - Camera movement
  static vec2 cursorPos;
  if(ImGui::IsMouseClicked(1)){
    cursorPos = utl_window->get_mouse_pose();

    ImGui::GetIO().MouseDrawCursor = false;
    utl_window->set_mouse_pose(vec2(center.x, center.y));
    camera->cam_move = true;
  }
  //Release - back to normal
  if(ImGui::IsMouseReleased(1) && camera->cam_move){
    utl_window->set_mouse_pose(cursorPos);
    camera->cam_move = false;
  }

  //---------------------------
}
void Control::control_mouse_wheel(){
  static int wheel_mode = 0;
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel + right clicked - Camera zoom
  if(io.MouseWheel && io.MouseDownDuration[1] >= 0.0f){
    cam_control->control_zoom(io.MouseWheel);
  }

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    wheel_mode++;
    if(wheel_mode >= 3) wheel_mode = 0;
  }

  //Wheel actions
  if(io.MouseWheel && io.MouseDownDuration[1] == -1){
    //Rotation quantity
    float radian = 5 * M_PI/180;
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
    eng::data::Entity* entity = sce_scene->get_selected_entity();
    sce_operation->make_rotation(entity, R);
  }

  //----------------------------
}

}
