#pragma once

#include <Utility/Specific/Common.h>

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace eng{class Node;}
namespace scene{class Database;}
namespace scene{class Loader;}
namespace scene{class Set;}
namespace scene{class Entity;}


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
  scene::Database* sce_database;
  scene::Loader* sce_loader;
  scene::Set* sce_set;
  scene::Entity* sce_entity;
};

}
