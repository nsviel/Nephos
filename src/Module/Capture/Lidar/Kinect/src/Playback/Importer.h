#pragma once

#include <Loader/src/Base/Importer.h>
#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}


namespace k4n::playback{

class Importer : public ldr::base::Importer
{
public:
  //Constructor / Destructor
  Importer(k4n::Node* node_k4n);
  ~Importer();

public:
  //Main function
  utl::media::File* import(utl::media::Path path);

  //Subfunction
  float find_mkv_ts_beg(string path);
  float find_mkv_ts_end(string path);

private:
  eng::Node* node_engine;
  k4n::dev::Swarm* k4n_swarm;
};

}