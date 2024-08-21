#pragma once

#include <string>
#include <vector>

namespace io::imp{class Node;}
namespace io::imp{class Structure;}
namespace io{class Transformation;}
namespace dat::elm{class Entity;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Set;}
namespace dat::elm{class Glyph;}
namespace dat::gph{class Selection;}
namespace dat::base{class Object;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace eng::trf{class Transformation;}
namespace eng::trf{class Operation;}
namespace dat::atr{class Field;}


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
  dat::gph::Graph* dat_graph;
  dat::elm::Set* dat_set;
  dat::elm::Glyph* dat_glyph;
  dat::gph::Selection* gph_selection;
  eng::trf::Transformation* trf_transform;
  eng::trf::Operation* trf_operation;
  dat::atr::Field* atr_field;
};

}
