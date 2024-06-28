#pragma once

#include <Loader/src/Base/Importer.h>
#include <string>

namespace k4n{class Node;}
namespace eng{class Node;}
namespace dat{class Graph;}
namespace dat::element{class Entity;}
namespace dat::element{class Set;}
namespace dat{class Glyph;}


namespace k4n::playback{

class Importer : public ldr::base::Importer
{
public:
  //Constructor / Destructor
  Importer(k4n::Node* node_k4n);
  ~Importer();

public:
  //Main function
  utl::base::Element* import(utl::base::Path path);

  //Subfunction
  float find_mkv_ts_beg(std::string path);
  float find_mkv_ts_end(std::string path);
  dat::base::Set* manage_set_parent();

private:
  k4n::Node* node_k4n;
  eng::Node* node_engine;
  dat::Graph* dat_graph;
  dat::element::Entity* dat_entity;
  dat::element::Set* dat_set;
  dat::Glyph* dat_glyph;
};

}
