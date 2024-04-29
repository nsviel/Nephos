#include "Graph.h"

#include <Scene/Namespace.h>
#include <Loader/Namespace.h>


namespace sce{

//Constructor / Destructor
Graph::Graph(sce::Node* node_scene){
  //---------------------------

  this->sce_loader = node_scene->get_scene_loader();

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::init(){
  //----------------------------

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
  //sce_loader->load_object(versaille_0);
  //sce_loader->load_object(versaille_2);
  //sce_loader->load_object(cerfav);
  //sce_loader->load_object(dragon);
  sce_loader->load_object(sphere);
  //sce_loader->load_dataset(pcap);

  //----------------------------
}

}
