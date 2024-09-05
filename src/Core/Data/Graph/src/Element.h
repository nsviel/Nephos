#pragma once

#include <memory>

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
  void remove_entity(std::shared_ptr<dat::base::Entity> entity);
  void remove_entity(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity);
  void remove_active_entity(std::shared_ptr<dat::base::Set> set);
  void remove_set(std::shared_ptr<dat::base::Set> set);

private:
  dat::elm::Set* dat_set;
  dat::gph::Structure* gph_struct;
  dat::gph::Selection* gph_selection;
};

}
