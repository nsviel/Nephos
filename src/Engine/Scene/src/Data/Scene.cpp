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


  //----------------------------
}

}
