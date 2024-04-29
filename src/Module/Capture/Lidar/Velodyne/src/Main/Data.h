#pragma once

#include <Utility/Specific/Common.h>

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace eng{class Node;}
namespace ldr{class Loader;}
namespace dat{class Database;}
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
  //Main functions
  void create_object();

private:
  eng::Node* node_engine;
  vld::structure::Main* vld_struct;
  dat::Database* sce_database;
  ldr::Loader* ldr_loader;
  dat::Set* sce_set;
  dat::Entity* sce_entity;
};

}
