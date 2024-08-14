#pragma once

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace eng{class Node;}
namespace io{class Importer;}
namespace dat::graph{class Graph;}
namespace dat::element{class Set;}
namespace dat::element{class Entity;}


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
  io::Importer* io_loader;
  dat::element::Set* dat_set;
  dat::element::Entity* dat_entity;
};

}
