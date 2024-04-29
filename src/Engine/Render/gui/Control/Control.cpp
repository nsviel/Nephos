#include "Control.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Scene/Namespace.h>
#include <Render/Namespace.h>
#include <Operation/Namespace.h>


namespace rnd::gui{

//Constructor / Destructor
Control::Control(rnd::Node* node_render){
  //---------------------------

  this->node_engine = node_render->get_node_engine();
  sce::Node* node_scene = node_engine->get_node_scene();
  cam::Node* node_camera = node_engine->get_node_camera();

  this->cam_manager = node_camera->get_camera_manager();
  this->cam_control = node_camera->get_camera_control();
  this->sce_database = node_scene->get_scene_database();
  this->sce_set = new sce::Set();
  this->ope_operation = new ope::Operation();
  this->gui_wheel = new rnd::gui::Wheel(node_render);

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

  utl::type::Set* set_main = sce_database->get_set_main();
  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Tab)){
      utl::type::Set* set_scene = sce_database->get_set_scene();
      sce_set->select_entity_next(set_scene);
      break;
    }

    //Suppr key - Delete selected
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
      utl::type::Set* set_scene = sce_database->get_set_scene();
      sce_set->remove_entity(set_scene, set_scene->selected_entity);
      break;
    }

    //R key - Reset
    if(ImGui::IsKeyPressed(ImGuiKey_R)){
      node_engine->reset();
      break;
    }
  }

  //----------------------------
}
void Control::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  utl::type::Set* set_main = sce_database->get_set_main();
  for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    if(!io.MouseDown[1]){
      utl::type::Set* set_scene = sce_database->get_set_scene();
      utl::type::Entity* entity = set_scene->selected_entity;

      //Shift speed up
      float translation_qtt = 0.01;
      if(io.KeysDown[340]){
        //translation_qtt = cloud_trans_speed * 5;
      }

      // Z key
      if(io.KeysDown[571]){
        vec3 translation = vec3(translation_qtt, 0, 0);
        ope_operation->make_translation(entity->set_parent, translation);
        break;
      }
      // S key
      if(io.KeysDown[564]){
        vec3 translation = vec3(-translation_qtt, 0, 0);
        ope_operation->make_translation(entity->set_parent, translation);
        break;
      }
      // D key
      if(io.KeysDown[549]){
        vec3 translation = vec3(0, translation_qtt, 0);
        ope_operation->make_translation(entity->set_parent, translation);
        break;
      }
      // Q key
      if(io.KeysDown[562]){
        vec3 translation = vec3(0, -translation_qtt, 0);
        ope_operation->make_translation(entity->set_parent, translation);
        break;
      }
      // A key
      if(io.KeysDown[546]){
        vec3 translation = vec3(0, 0, translation_qtt);
        ope_operation->make_translation(entity->set_parent, translation);
        break;
      }
      // E key
      if(io.KeysDown[550]){
        vec3 translation = vec3(0, 0, -translation_qtt);
        ope_operation->make_translation(entity->set_parent, translation);
        break;
      }
    }
  }

  //----------------------------
}

//Mouse
void Control::control_mouse_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    gui_wheel->change_mode();
  }

  //Wheel actions
  if(io.MouseWheel && io.MouseDownDuration[1] == -1){
    float direction = math::sign(io.MouseWheel);
    gui_wheel->make_action(direction);
  }

  //----------------------------
}


}
