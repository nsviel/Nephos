#include "Manager.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>
#include <Vulkan/Namespace.h>


namespace cam{

//Constructor / Destructor
Manager::Manager(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->node_engine = node_camera->get_node_engine();
  this->vk_screenshot = node_vulkan->get_vk_screenshot();
  this->cam_struct = node_camera->get_cam_struct();
  this->cam_control = node_camera->get_cam_control();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_camera(){
  dat::Node* node_data = node_engine->get_node_data();
  dat::Graph* dat_graph = node_data->get_dat_graph();
  dat::Set* dat_set = node_data->get_dat_set();
  dat::Glyph* dat_glyph = node_data->get_dat_glyph();
  dat::base::Set* set_scene = dat_graph->get_set_scene();
  //---------------------------

  cam::Entity* camera = new cam::Entity();
  camera->ID = cam_struct->ID++;
  camera->name = "camera_" + std::to_string(camera->ID);
  camera->is_suppressible = false;
  camera->pose.movable = false;

  dat_glyph->insert_glyph(camera);
  dat_set->insert_entity(set_scene, camera);

  cam_struct->vec_camera.push_back(camera);
  cam_struct->cam_current = camera;
  cam_control->set_camera_mode(camera);

  //---------------------------
}
void Manager::reset_camera(){
  //---------------------------

  for(int i=0; i<cam_struct->vec_camera.size(); i++){
    cam::Entity* camera = cam_struct->vec_camera[i];
    camera->reset();
  }

  //---------------------------
}
void Manager::make_screenshot(){
  //---------------------------

  vk_screenshot->make_screenshot();

  //---------------------------
}

}
