#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace dat{class Entity;}
namespace dat{class Graph;}
namespace dat{class Set;}
namespace dat{class Glyph;}
namespace dat{class Selection;}
namespace dat::base{class Object;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace ope{class Transformation;}
namespace ope{class Operation;}


namespace ldr::importer{

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
  void ope_clean();
  void ope_color(dat::base::Entity* entity);
  void ope_transformation(dat::base::Entity* entity);
  void ope_insertion(dat::base::Entity* entity);

private:
  ldr::Structure* ldr_struct;
  dat::Entity* dat_entity;
  dat::Graph* dat_graph;
  dat::Set* dat_set;
  dat::Glyph* dat_glyph;
  dat::Selection* dat_selection;
  ope::Transformation* ope_transform;
  ope::Operation* ope_operation;
};

}
