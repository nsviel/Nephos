#pragma once

namespace dat::gph{class Node;}
namespace dat::gph{class Structure;}
namespace dat::gph{class Selection;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat::gph{

class Element
{
public:
  //Constructor / Destructor
  Element(dat::gph::Node* node_graph);
  ~Element();

public:
  //Main function
  void remove_entity(dat::base::Set* set, dat::base::Entity* entity);

private:
  dat::elm::Set* dat_set;
  dat::gph::Structure* gph_struct;
  dat::gph::Selection* gph_selection;
};

}
