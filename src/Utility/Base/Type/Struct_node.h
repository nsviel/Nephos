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

  Panel* new_panel(string name, bool value){
    Panel* panel = new Panel(name, value);
    this->vec_panel.push_back(panel);
    return panel;
  }

  inline vector<Panel*> get_vec_panel(){return vec_panel;}

protected:
  utl::type::Node* node_up;
  vector<utl::type::Node*> node_down;
  vector<Panel*> vec_panel;
};

}
