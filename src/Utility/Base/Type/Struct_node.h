#pragma once

#include <Utility/Specific/common.h>

using Panel = std::pair<std::string, bool>;


namespace utl::type{

class Node
{
public:
  Node(){}
  ~Node(){}

public:
  //Main function
  virtual void init(){}
  virtual void loop(){}
  virtual void gui(){}
  virtual void reset(){}
  virtual void exit(){}
  virtual void wait(){}

  inline vector<Panel*> get_vec_panel(){return vec_panel;}

protected:
  vector<Panel*> vec_panel;
};

}
