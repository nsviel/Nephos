#include "Control.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>
#include <Render/Namespace.h>
#include <Operation/Namespace.h>
#include <glm/glm.hpp>


namespace rnd::gui{

//Constructor / Destructor
Control::Control(rnd::Node* node_render){
  //---------------------------

  eng::Node* node_engine = node_render->get_node_engine();
  dat::Node* node_data = node_engine->get_node_data();
  cam::Node* node_camera = node_engine->get_node_camera();

  this->node_engine = node_engine;
  this->cam_manager = node_camera->get_manager();
  this->cam_control = node_camera->get_control();
  this->dat_graph = node_data->get_data_graph();
  this->dat_set = node_data->get_data_set();
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

  dat::base::Set* set_main = dat_graph->get_set_main();
  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Tab)){
      dat::base::Set* set_scene = dat_graph->get_set_graph();
      dat_set->active_next_entity(set_scene);
      break;
    }

    //Suppr key - Delete selected
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
      dat::base::Set* set_scene = dat_graph->get_set_graph();
      dat_set->remove(set_scene, set_scene->active_entity);
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

  dat::base::Set* set_main = dat_graph->get_set_main();
  for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    if(!io.MouseDown[1]){
      utl::type::Element* element = dat_graph->get_selection();

      //Shift speed up
      float translation_qtt = 0.01;
      if(io.KeysDown[340]){
        //translation_qtt = cloud_trans_speed * 5;
      }

      // Z key
      if(io.KeysDown[571]){
        glm::vec3 translation = glm::vec3(translation_qtt, 0, 0);
        ope_operation->make_translation(element, translation);
        break;
      }
      // S key
      if(io.KeysDown[564]){
        glm::vec3 translation = glm::vec3(-translation_qtt, 0, 0);
        ope_operation->make_translation(element, translation);
        break;
      }
      // D key
      if(io.KeysDown[549]){
        glm::vec3 translation = glm::vec3(0, translation_qtt, 0);
        ope_operation->make_translation(element, translation);
        break;
      }
      // Q key
      if(io.KeysDown[562]){
        glm::vec3 translation = glm::vec3(0, -translation_qtt, 0);
        ope_operation->make_translation(element, translation);
        break;
      }
      // A key
      if(io.KeysDown[546]){
        glm::vec3 translation = glm::vec3(0, 0, translation_qtt);
        ope_operation->make_translation(element, translation);
        break;
      }
      // E key
      if(io.KeysDown[550]){
        glm::vec3 translation = glm::vec3(0, 0, -translation_qtt);
        ope_operation->make_translation(element, translation);
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
