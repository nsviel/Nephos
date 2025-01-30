#include "Node.h"

#include <IO/Namespace.h>
#include <Format/Namespace.h>


namespace fmt{

//Constructor / Destructor
Node::Node(io::Node* node_io){
  //---------------------------

  io::imp::Node* node_importer = node_io->get_node_importer();
  io::exp::Node* node_exporter = node_io->get_node_exporter();

  this->io_importer = node_importer->get_io_importer();
  this->io_exporter = node_exporter->get_io_exporter();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  //Importer
  io_importer->insert_importer(new fmt::ply::Importer());
  io_importer->insert_importer(new fmt::obj::Importer());
  io_importer->insert_importer(new fmt::gltf::Importer());
  io_importer->insert_importer(new fmt::csv::Importer());
  io_importer->insert_importer(new fmt::pts::Importer());
  io_importer->insert_importer(new fmt::ptx::Importer());
  io_importer->insert_importer(new fmt::xyz::Importer());
  io_importer->insert_importer(new fmt::hdf5::Importer());

  //Exporter
  io_exporter->insert_exporter(new fmt::ply::Exporter());
  io_exporter->insert_exporter(new fmt::pts::Exporter());
  io_exporter->insert_exporter(new fmt::hdf5::Exporter());

  //---------------------------
}

}
