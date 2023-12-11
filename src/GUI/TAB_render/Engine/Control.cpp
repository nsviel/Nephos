#include "Control.h"

#include <Node/GUI.h>
#include <Node/Engine.h>
#include <Node/Utility.h>
#include <UTL_window/UTL_window.h>
#include <ENG_data/ENG_data.h>
#include <UTL_function/fct_math.h>
#include <ENG_data/ENG_scene/ENG_scene.h>
#include <ENG_data/ENG_data.h>
#include <ENG_camera/ENG_camera.h>
#include <ENG_operation/Transformation/Transformation.h>


namespace gui::engine{

//Constructor / Destructor
Control::Control(GUI* gui){
  //---------------------------

  Utility* utility = gui->get_utility();
  Engine* engine = gui->get_engine();
  ENG_data* eng_data = engine->get_eng_data();

  this->engine = gui->get_engine();
  this->utl_window = utility->get_utl_window();
  this->camera = engine->get_camera();
  this->eng_camera = engine->get_eng_camera();
  this->eng_scene = eng_data->get_eng_scene();
  this->transformManager = new Transformation();

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

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Tab)){
      eng_scene->selected_object_next();
      break;
    }

    //Suppr key - Delete selected
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
      data::Set* set = eng_scene->get_set_scene();
      eng::structure::Object* object = set->selected_obj;
      eng_scene->selected_object_next();
      eng_scene->delete_scene_object(object);
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
        eng_camera->control("up", is_fast);
      }

      //S key or Down key
      if(io.KeysDown[564] || io.KeysDown[516]){
        eng_camera->control("down", is_fast);
      }

      //Q key or Left key
      if(io.KeysDown[562] || io.KeysDown[513]){
        eng_camera->control("left", is_fast);
      }

      //D key or Left key
      if(io.KeysDown[549] || io.KeysDown[514]){
        eng_camera->control("right", is_fast);
      }
    }
  }

  //---------------------------
}
void Control::control_keyboard_translation(){
  data::Set* set = eng_scene->get_set_scene();
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    if(!io.MouseDown[1]){
      float transCoef = 0.01;

      //Shift speed up
      if(io.KeysDown[340]){
        //transCoef = cloud_trans_speed * 5;
      }

      // Z key
      if(io.KeysDown[571]){
        vec3 translation = vec3(transCoef, 0, 0);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // S key
      if(io.KeysDown[564]){
        vec3 translation = vec3(-transCoef, 0, 0);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // D key
      if(io.KeysDown[549]){
        vec3 translation = vec3(0, transCoef, 0);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // Q key
      if(io.KeysDown[562]){
        vec3 translation = vec3(0, -transCoef, 0);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // A key
      if(io.KeysDown[546]){
        vec3 translation = vec3(0, 0, transCoef);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // E key
      if(io.KeysDown[550]){
        vec3 translation = vec3(0, 0, -transCoef);
        transformManager->make_translation(set->selected_obj, translation);
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
    eng_camera->compute_zoom(io.MouseWheel);
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
    data::Set* set = eng_scene->get_set_scene();
    eng::structure::Object* object = set->selected_obj;
    transformManager->make_rotation(object, object->COM, R);
  }

  //----------------------------
}

}
