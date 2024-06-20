#include "Init.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Loader/Namespace.h>


namespace sce{

//Constructor / Destructor
Init::Init(sce::Node* node_scene){
  //---------------------------

  eng::Node* node_engine = node_scene->get_node_engine();
  ldr::Node* node_loader = node_engine->get_node_loader();

  this->ldr_loader = node_loader->get_ldr_importer();

  //---------------------------
}
Init::~Init(){}

//Main function
void Init::init(){
  //----------------------------

  this->load_entity();

  //----------------------------
}

//Subfunction
void Init::load_entity(){
  //----------------------------

  //utl::base::Path versaille_0("/home/aether/Desktop/versaille_0.mkv");
  /*versaille_0.transformation = "/home/aether/Desktop/versaille_0.json";

  utl::base::Path versaille_2;
  versaille_2.data = "/home/aether/Desktop/versaille_2.mkv";
  versaille_2.transformation = "/home/aether/Desktop/versaille_2.json";

  utl::base::Path cerfav;
  cerfav.data = "/home/aether/Desktop/cerfav_3_1.mkv";

  utl::base::Path dragon;
  dragon.data = "/home/aether/Desktop/Nephos/media/point_cloud/dragon.ply";

  utl::base::Path sphere;
  sphere.data = "/home/aether/Desktop/Sphere_good.mkv";
  //sphere.data = "/home/aether/Desktop/bench_1.mkv";

  utl::base::Path pcap;
  pcap.data = "/home/aether/Desktop/pcap_test.pcap";

  utl::base::Path mire;
  mire.data = "/home/aether/Desktop/Mire.mkv";

  //Create playback list
  //ldr_loader->load_object(versaille_0);
  //ldr_loader->load_object(versaille_2);
  //ldr_loader->load_object(cerfav);
  //ldr_loader->load_object(dragon);
  //ldr_loader->load_object(sphere);
  //ldr_loader->load_set(pcap);
  //ldr_loader->load_object(mire);
  ldr_loader->load_object(sphere);*/

  //----------------------------
}

}
