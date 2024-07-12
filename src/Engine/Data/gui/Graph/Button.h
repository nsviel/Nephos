#pragma once

#include <string>

namespace dat{class Node;}
namespace dat::element{class Set;}


namespace dat::gui::graph{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::Node* node_data);
  ~Panel();

public:
  //Main function


private:
  dat::element::Set* dat_set;
};

}
