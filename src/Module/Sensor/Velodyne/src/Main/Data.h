#pragma once

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace eng{class Node;}
namespace ldr::io{class Importer;}
namespace dat{class Graph;}
namespace dat{class Set;}
namespace dat{class Entity;}


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
  dat::Graph* dat_graph;
  ldr::io::Importer* ldr_loader;
  dat::Set* dat_set;
  dat::Entity* dat_entity;
};

}
