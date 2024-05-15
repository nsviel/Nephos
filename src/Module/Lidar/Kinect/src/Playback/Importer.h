#pragma once

#include <Loader/src/Base/Importer.h>
#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace eng{class Node;}
namespace dat{class Graph;}
namespace dat{class Entity;}
namespace dat{class Set;}


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
  k4n::dev::Master* manage_master();

private:
  k4n::Node* node_k4n;
  eng::Node* node_engine;
  dat::Graph* dat_graph;
  dat::Entity* dat_entity;
  dat::Set* dat_set;
};

}
