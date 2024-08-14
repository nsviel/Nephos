#pragma once

#include <string>

namespace dat::graph{class Node;}
namespace dat::element{class Set;}
namespace dat::element{class Entity;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dat::graph::gui{

class Button
{
public:
  //Constructor / Destructor
  Button(dat::graph::Node* node_graph);
  ~Button();

public:
  //Main function
  void button_locked(dat::base::Set* set);
  void button_visibility(dat::base::Set* set);
  void button_visibility(dat::base::Entity* entity);
  void button_remove(dat::base::Set* set, dat::base::Entity* entity);
  void button_remove(dat::base::Set* set);

private:
  dat::element::Set* dat_set;
  dat::element::Entity* dat_entity;
};

}