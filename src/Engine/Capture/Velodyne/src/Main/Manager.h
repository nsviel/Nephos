#pragma once

#include <Utility/Specific/Common.h>

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace eng::scene{class Database;}
namespace eng::scene{class Loader;}
namespace eng::scene{class Set;}


namespace vld::main{

class Manager
{
public:
  //Constructor / Destructor
  Manager(vld::Node* node_vld);
  ~Manager();

public:
  //Main function
  void init();

private:
  vld::structure::Main* vld_struct;
  eng::scene::Database* sce_database;
  eng::scene::Loader* sce_loader;
  eng::scene::Set* sce_set;
};

}
