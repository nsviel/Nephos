#pragma once

#include <Utility/Specific/Common.h>

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace vld::thread{class Server;}
namespace eng{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene{class Loader;}
namespace eng::scene{class Set;}
namespace eng::scene{class Entity;}


namespace vld::main{

class Capture
{
public:
  //Constructor / Destructor
  Capture(vld::Node* node_vld);
  ~Capture();

public:
  //Main functions
  void init();
  void clean();

private:
  eng::Node* node_engine;
  vld::structure::Main* vld_struct;
  vld::thread::Server* vld_server;
  eng::scene::Database* sce_database;
  eng::scene::Loader* sce_loader;
  eng::scene::Set* sce_set;
  eng::scene::Entity* sce_entity;
};

}
