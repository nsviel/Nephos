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

  utl::file::Path path_1;
  path_1.data = "/home/aether/Desktop/versaille_0.mkv";
  path_1.transformation = "/home/aether/Desktop/versaille_0.json";

  utl::file::Path path_2;
  path_2.data = "/home/aether/Desktop/versaille_2.mkv";
  path_2.transformation = "/home/aether/Desktop/versaille_2.json";

  utl::file::Path path_3;
  path_3.data = "/home/aether/Desktop/output.mkv";

  utl::file::Path path_4;
  path_4.data = "/home/aether/Desktop/cerfav_3_1.mkv";

  utl::file::Path path_5;
  path_5.data = "/home/aether/Desktop/Nephos/media/point_cloud/dragon.ply";

  utl::file::Path path_6;
  path_6.data = "/home/aether/Desktop/sphere_test.mkv";

  utl::file::Path path_7;
  path_7.data = "/home/aether/Desktop/bench_ground_2.mkv";

  //Create playback list
  //sce_loader->load_object(path_1);
  //sce_loader->load_object(path_2);
  //sce_loader->load_object(path_3);
  //sce_loader->load_object(path_4);
  //sce_loader->load_object(path_6);
  sce_loader->load_object(path_7);

  //----------------------------
}

}
