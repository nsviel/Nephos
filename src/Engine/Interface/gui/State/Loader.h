#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>

namespace itf{class Node;}
namespace itf::state{class Manager;}
namespace itf::state{class Structure;}
namespace utl::base{class Path;}


namespace itf::state{

class Loader
{
public:
  //Constructor / Destructor
  Loader(itf::state::Manager* manager);
  ~Loader();

public:
  //Main function
  void load_state(std::string path);

  //Subfunction
  void read_ini_settings(std::string& path);
  void read_panel(std::string& path);

private:
  itf::Node* node_interface;
  itf::state::Structure* sta_struct;
};

}
