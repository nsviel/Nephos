#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}


namespace k4n{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer(k4n::Node* node_k4n);
  ~Importer();

public:
  //Main function
  utl::File* import(utl::Path path);

private:
  eng::Node* node_engine;
  k4n::dev::Swarm* k4n_swarm;
};

}
