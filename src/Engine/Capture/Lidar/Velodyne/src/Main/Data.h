#pragma once

#include <Utility/Specific/Common.h>

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace eng{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene{class Loader;}
namespace eng::scene{class Set;}
namespace eng::scene{class Entity;}


namespace vld::main{

class Data
{
public:
  //Constructor / Destructor
  Data(vld::Node* node_vld);
  ~Data();

public:
  //Main functions
  void create_object();

private:
  eng::Node* node_engine;
  vld::structure::Main* vld_struct;
  eng::scene::Database* sce_database;
  eng::scene::Loader* sce_loader;
  eng::scene::Set* sce_set;
  eng::scene::Entity* sce_entity;
};

}
