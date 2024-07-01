#pragma once

#include <Utility/Base/Type/Path.h>
#include <vector>
#include <string>

namespace gui{class Node;}
namespace utl::base{class Path;}


namespace gui::interface{

class Demo
{
public:
  //Constructor / Destructor
  Demo(gui::Node* gui);
  ~Demo();

public:
  //Main function
  void loop();

  //Subfunction
  void open_demo_file();

  inline bool* get_show_demo(){return &show_demo;}

private:
  bool show_demo = false;
};

}
