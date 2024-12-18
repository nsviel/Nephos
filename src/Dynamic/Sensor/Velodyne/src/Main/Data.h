#pragma once

namespace vld{class Node;}
namespace vld{class Structure;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Set;}
namespace dat::elm{class Entity;}


namespace vld::main{

class Data
{
public:
  //Constructor / Destructor
  Data(vld::Node* node_velodyne);
  ~Data();

public:
  //Main function
  void create_object();

private:
  vld::Structure* vld_struct;
  dat::gph::Graph* dat_graph;
  dat::elm::Set* dat_set;
  dat::elm::Entity* dat_entity;
};

}
