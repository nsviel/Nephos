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

  utl::base::Path versaille_0("/home/nsv/Desktop/versaille_0.mkv");
  utl::base::Path versaille_0_t("/home/nsv/Desktop/versaille_0.json");

  utl::base::Path versaille_2("/home/nsv/Desktop/versaille_2.mkv");
  utl::base::Path versaille_2_t("/home/nsv/Desktop/versaille_2.json");

  utl::base::Path cerfav("/home/nsv/Desktop/cerfav_3_1.mkv");

  utl::base::Path dragon("/home/nsv/Desktop/Nephos/media/point_cloud/dragon.ply");
  utl::base::Path bunny("/home/nsv/Desktop/Nephos/media/point_cloud/bunny.ply");

  utl::base::Path sphere("/home/nsv/Desktop/Sphere_good.mkv");

  utl::base::Path pcap("/home/nsv/Desktop/pcap_test.pcap");

  utl::base::Path mire("/home/nsv/Desktop/Mire.mkv");

  utl::base::Path ply("/home/nsv/Desktop/Point_cloud/ply/hippo2.ply");
  utl::base::Path cath("/home/nsv/Desktop/Point_cloud/ply/Cathedral/pts_regis_01.ply");
  utl::base::Path pts("/home/nsv/Desktop/Point_cloud/pts/cloud.pts");
  utl::base::Path bag("/home/nsv/Desktop/intel.bag");

  utl::base::Path viking("/home/nsv/Desktop/Point_cloud/obj/viking/viking_room.obj");
  utl::base::Path viking_tex("/home/nsv/Desktop/Point_cloud/obj/viking/viking_room.png");



  //Create playback list
  io_struct->operation.with_clearing = false;
  io_loader->load_object(versaille_0, versaille_0_t);
  //io_loader->load_object(versaille_2, versaille_2_t);
  //io_loader->load_object(cerfav);
  //io_loader->load_object(pts);
  //io_loader->load_object(sphere);
  //io_loader->load_set(pcap);
  //io_loader->load_object(mire);
  //io_loader->load_object(cath);
  //io_loader->load_object(dragon);
  //io_loader->load_object(bunny);
  //io_loader->load_object_textured(viking, viking_tex);

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
