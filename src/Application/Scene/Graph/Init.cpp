#include "Init.h"

#include <Core/Namespace.h>
#include <Scene/Namespace.h>
#include <Importer/Namespace.h>
#include <IO/Namespace.h>


namespace sce{

//Constructor / Destructor
Init::Init(sce::Node* node_scene){
  //---------------------------

  core::Node* node_core = node_scene->get_node_core();
  io::Node* node_io = node_core->get_node_io();
  io::imp::Node* node_importer = node_io->get_node_importer();

  this->io_loader = node_importer->get_io_loader();
  this->io_struct = node_importer->get_io_struct();

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

  utl::base::Path versaille_0("/home/aether/Desktop/versaille_0.mkv");
  utl::base::Path versaille_0_t("/home/aether/Desktop/versaille_0.json");

  utl::base::Path versaille_2("/home/aether/Desktop/versaille_2.mkv");
  utl::base::Path versaille_2_t("/home/aether/Desktop/versaille_2.json");

  utl::base::Path cerfav("/home/aether/Desktop/cerfav_3_1.mkv");

  utl::base::Path dragon("/home/aether/Desktop/Nephos/media/point_cloud/dragon.ply");

  utl::base::Path sphere("/home/aether/Desktop/Sphere_good.mkv");

  utl::base::Path pcap("/home/aether/Desktop/pcap_test.pcap");

  utl::base::Path mire("/home/aether/Desktop/Mire.mkv");

  utl::base::Path ply("/home/aether/Desktop/Point_cloud/ply/hippo2.ply");
  utl::base::Path cath("/home/aether/Desktop/Point_cloud/ply/Cathedral/pts_regis_01.ply");
  utl::base::Path pts("/home/aether/Desktop/Point_cloud/pts/cloud.pts");
  utl::base::Path bag("/home/aether/Desktop/intel.bag");



  //Create playback list
  io_struct->operation.with_clearing = false;
  //io_loader->load_object(versaille_0, versaille_0_t);
  //io_loader->load_object(versaille_2, versaille_2_t);
  //io_loader->load_object(cerfav);
  //io_loader->load_object(pts);
  //io_loader->load_object(sphere);
  //io_loader->load_set(pcap);
  //io_loader->load_object(mire);
  //io_loader->load_object(cath);
  //io_loader->load_object(dragon);

  io_loader->load_object(bag);

  /*
  io_loader->load_object(dragon);
  io_loader->load_object(dragon);
  io_loader->load_object(dragon);
  io_loader->load_object(dragon);
  io_loader->load_object(dragon);
  io_loader->load_object(dragon);
  */

  //----------------------------
}

}
