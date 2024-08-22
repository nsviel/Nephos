#pragma once

#include <string>

namespace dat::gph{class Node;}
namespace dat::gph{class Element;}
namespace dat::elm{class Set;}
namespace dat::elm{class Entity;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dat::gph::gui{

class Button
{
public:
  //Constructor / Destructor
  Button(dat::gph::Node* node_graph);
  ~Button();

public:
  //Main function
  void button_locked(dat::base::Set* set);
  void button_visibility(dat::base::Set* set);
  void button_visibility(dat::base::Entity* entity);
  void button_remove(dat::base::Set* set, dat::base::Entity* entity);
  void button_remove(dat::base::Set* set);

private:
  dat::elm::Set* dat_set;
  dat::elm::Entity* dat_entity;
  dat::gph::Element* gph_element;
};

}
