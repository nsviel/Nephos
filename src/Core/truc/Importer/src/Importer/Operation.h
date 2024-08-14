#pragma once

#include <string>
#include <vector>

namespace io::imp{class Node;}
namespace io::imp{class Structure;}
namespace io{class Transformation;}
namespace dat::elm{class Entity;}
namespace dat::graph{class Graph;}
namespace dat::elm{class Set;}
namespace dat{class Glyph;}
namespace dat::graph{class Selection;}
namespace dat::base{class Object;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace ope{class Transformation;}
namespace ope{class Operation;}
namespace utl::base{class Attribut;}


namespace io::imp{

class Operation
{
public:
  //Constructor / Destructor
  Operation(io::imp::Node* node_importer);
  ~Operation();

public:
  //Main function
  void insert_object(dat::base::Object* object);
  void insert_set(dat::base::Set* set);

  //Subfunction
  void ope_clean();
  void ope_color(dat::base::Entity* entity);
  void ope_transformation(dat::base::Entity* entity);
  void ope_insertion(dat::base::Entity* entity);

private:
  io::imp::Structure* io_struct;
  io::Transformation* io_transformation;
  dat::elm::Entity* dat_entity;
  dat::graph::Graph* dat_graph;
  dat::elm::Set* dat_set;
  dat::Glyph* dat_glyph;
  dat::graph::Selection* dat_selection;
  ope::Transformation* ope_transform;
  ope::Operation* ope_operation;
  utl::base::Attribut* utl_attribut;
};

}
