#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Swarm;}


namespace eng::k4n{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer(eng::k4n::Node* node_k4n);
  ~Importer();

public:
  //Main function
  void import(string path);

private:
  eng::Node* node_engine;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
