#pragma once

#include <Utility/Specific/Common.h>

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace eng{class Node;}
namespace sce{class Database;}
namespace ldr{class Loader;}
namespace sce{class Set;}
namespace sce{class Entity;}


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
  sce::Database* sce_database;
  ldr::Loader* sce_loader;
  sce::Set* sce_set;
  sce::Entity* sce_entity;
};

}
