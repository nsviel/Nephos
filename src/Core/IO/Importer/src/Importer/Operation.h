#pragma once

#include <memory>
#include <string>
#include <vector>

namespace io::imp{class Node;}
namespace io::imp{class Structure;}
namespace dat::elm{class Entity;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Set;}
namespace dat::elm{class Glyph;}
namespace dat::gph{class Selection;}
namespace dat::gph{class Element;}
namespace dat::base{class Object;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace eng::trf{class Transformation;}
namespace eng::trf{class Operation;}
namespace eng::trf{class IO;}
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
  void insert_object(std::shared_ptr<dat::base::Object> object);
  void insert_set(std::shared_ptr<dat::base::Set> set);

  //Subfunction
  void ope_clean();
  void ope_color(std::shared_ptr<dat::base::Object> object);
  void ope_transformation(std::shared_ptr<dat::base::Object> object);
  void ope_insertion(std::shared_ptr<dat::base::Object> object);

private:
  io::imp::Structure* io_struct;
  dat::elm::Entity* dat_entity;
  dat::gph::Graph* dat_graph;
  dat::elm::Set* dat_set;
  dat::elm::Glyph* dat_glyph;
  dat::gph::Element* gph_element;
  dat::gph::Selection* gph_selection;
  eng::trf::Transformation* trf_transform;
  eng::trf::Operation* trf_operation;
  eng::trf::IO* trf_io;
  dat::atr::Field* atr_field;
};

}
