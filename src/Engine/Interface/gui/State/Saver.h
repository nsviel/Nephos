#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>

namespace itf{class Node;}
namespace itf::state{class Manager;}
namespace itf::state{class Structure;}
namespace utl::base{class Path;}


namespace itf::state{

class Saver
{
public:
  //Constructor / Destructor
  Saver(itf::state::Manager* manager);
  ~Saver();

public:
  //Main function
  void save_state();

  //Subfunction
  void write_ini_settings(std::string& path);
  void write_panel(std::string& path);

private:
  itf::Node* node_interface;
  itf::state::Structure* sta_struct;
};

}
