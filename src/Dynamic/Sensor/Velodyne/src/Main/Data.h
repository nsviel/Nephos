#pragma once

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace core{class Node;}
namespace io::imp{class Importer;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Set;}
namespace dat::elm{class Entity;}


namespace vld::main{

class Data
{
public:
  //Constructor / Destructor
  Data(vld::Node* node_vld);
  ~Data();

public:
  //Main function
  void create_object();

private:
  core::Node* node_core;
  vld::structure::Main* vld_struct;
  dat::gph::Graph* dat_graph;
  io::imp::Importer* io_loader;
  dat::elm::Set* dat_set;
  dat::elm::Entity* dat_entity;
};

}
