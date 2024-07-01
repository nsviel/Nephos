#pragma once

#include <Utility/Base/Type/Path.h>
#include <vector>
#include <string>

namespace gui{class Node;}
namespace utl::base{class Path;}


namespace gui::state{

class IO
{
public:
  //Constructor / Destructor
  IO(gui::Node* gui);
  ~IO();

public:
  //Main function
  void state_save(std::string path);
  void state_load(std::string path);

private:

};

}
