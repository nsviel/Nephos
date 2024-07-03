#pragma once

#include <string>

namespace itf{class Node;}
namespace itf::state{class Saver;}
namespace itf::state{class Loader;}
namespace itf::state{class Logic;}
namespace itf::state{class Structure;}


namespace itf::state{

class Manager
{
public:
  //Constructor / Destructor
  Manager(itf::Node* node_interface);
  ~Manager();

public:
  //Main function
  void init();
  void loop();
  void gui();

  inline itf::Node* get_node_interface(){return node_interface;}
  inline itf::state::Structure* get_sta_struct(){return sta_struct;}

private:
  itf::Node* node_interface;
  itf::state::Saver* gui_save;
  itf::state::Loader* gui_load;
  itf::state::Logic* gui_logic;
  itf::state::Structure* sta_struct;
};

}
