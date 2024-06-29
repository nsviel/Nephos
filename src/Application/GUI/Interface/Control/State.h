#pragma once

#include <Utility/Base/Type/Path.h>
#include <vector>
#include <string>

namespace gui{class Node;}
namespace utl::base{class Path;}


namespace gui::interface{

class State
{
public:
  //Constructor / Destructor
  State(gui::Node* gui);
  ~State();

public:
  //Main function
  void save_state();
  void load_state();

  inline std::vector<std::string> get_vec_path(){return vec_path;}

private:
  std::vector<std::string> vec_path;
  utl::base::Path path;
};

}
