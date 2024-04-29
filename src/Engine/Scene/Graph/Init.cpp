#include "Init.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Loader/Namespace.h>


namespace sce{

//Constructor / Destructor
Init::Init(sce::Node* node_scene){
  //---------------------------

  node_engine = node_scene->get_node_engine();



  //---------------------------
}
Init::~Init(){}

//Main function
void Init::init(){
  //----------------------------
  ldr::Node* node_loader = node_engine->get_node_loader();

  this->ldr_loader = node_loader->get_loader();
  utl::Path versaille_0;
  versaille_0.data = "/home/aether/Desktop/versaille_0.mkv";
  versaille_0.transformation = "/home/aether/Desktop/versaille_0.json";

  utl::Path versaille_2;
  versaille_2.data = "/home/aether/Desktop/versaille_2.mkv";
  versaille_2.transformation = "/home/aether/Desktop/versaille_2.json";

  utl::Path cerfav;
  cerfav.data = "/home/aether/Desktop/cerfav_3_1.mkv";

  utl::Path dragon;
  dragon.data = "/home/aether/Desktop/Nephos/media/point_cloud/dragon.ply";

  utl::Path sphere;
  sphere.data = "/home/aether/Desktop/bench_1.mkv";

  utl::Path pcap;
  pcap.data = "/home/aether/Desktop/pcap_test.pcap";

  //Create playback list
  //ldr_loader->load_object(versaille_0);
  //ldr_loader->load_object(versaille_2);
  //ldr_loader->load_object(cerfav);
  //ldr_loader->load_object(dragon);
  ldr_loader->load_object(sphere);
  //ldr_loader->load_dataset(pcap);

  //----------------------------
}

}
