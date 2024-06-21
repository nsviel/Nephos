#pragma once

namespace k4n{class Node;}
namespace k4n{class Structure;}


namespace k4n::playback{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(k4n::Node* node_k4n);
  ~Configuration();

public:
  //Main function

private:
  k4n::Structure* k4n_struct;
};

}
