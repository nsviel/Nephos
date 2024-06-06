#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace dat{class Entity;}
namespace dat{class Graph;}
namespace dat{class Set;}
namespace dat{class Glyph;}
namespace dat::base{class Object;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace ldr::processing{

class Operation
{
public:
  //Constructor / Destructor
  Operation(ldr::Node* node_loader);
  ~Operation();

public:
  //Main functions
  void insert_object(dat::base::Object* object);
  void insert_set(dat::base::Set* set);

  //Subfunction
  void transformation_from_file(dat::base::Entity* entity);

private:
  dat::Entity* dat_entity;
  dat::Graph* dat_graph;
  dat::Set* dat_set;
  dat::Glyph* dat_glyph;
};

}
