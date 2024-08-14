#pragma once

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace eng{class Node;}
namespace io::imp{class Importer;}
namespace dat::graph{class Graph;}
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
  eng::Node* node_engine;
  vld::structure::Main* vld_struct;
  dat::graph::Graph* dat_graph;
  io::imp::Importer* io_loader;
  dat::elm::Set* dat_set;
  dat::elm::Entity* dat_entity;
};

}
