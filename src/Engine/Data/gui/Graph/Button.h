#pragma once

#include <string>

namespace dat{class Node;}
namespace dat::element{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dat::gui::graph{

class Button
{
public:
  //Constructor / Destructor
  Button(dat::Node* node_data);
  ~Button();

public:
  //Main function
  void button_remove(dat::base::Set* set, dat::base::Entity* entity);

private:
  dat::element::Set* dat_set;
};

}
