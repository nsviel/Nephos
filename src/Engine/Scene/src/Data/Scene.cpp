#include "Scene.h"

#include <Scene/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Scene::Scene(eng::scene::Node* node_scene){
  //---------------------------

  this->sce_loader = node_scene->get_scene_loader();

  //---------------------------
}
Scene::~Scene(){}

//Main function
void Scene::init(){
  //----------------------------

  utl::file::Entity file_1;
  file_1.path_data = "/home/aether/Desktop/versaille_0.mkv";
  file_1.path_transformation = "/home/aether/Desktop/versaille_0.json";

  utl::file::Entity file_2;
  file_2.path_data = "/home/aether/Desktop/versaille_2.mkv";
  file_2.path_transformation = "/home/aether/Desktop/versaille_2.json";

  utl::file::Entity file_3;
  file_3.path_data = "/home/aether/Desktop/output.mkv";

  utl::file::Entity file_4;
  file_4.path_data = "/home/aether/Desktop/cerfav_3_1.mkv";

  utl::file::Entity file_5;
  file_5.path_data = "/home/aether/Desktop/Nephos/media/point_cloud/dragon.ply";

  //Create playback list
  sce_loader->load_data(&file_1);
  //this->create_sensor_playback(file_1);
  //this->create_sensor_playback(file_2);
  //this->create_sensor_playback(file_4);

  //----------------------------
}

}
