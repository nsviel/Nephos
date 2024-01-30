#pragma once

#include <Utility/Specific/common.h>

struct Panel{
  //---------------------------

  Panel(const string& n, const string& i, bool o) : name(n), icon(i), is_open(o){}

  string name;
  string icon;
  bool is_open;

  //---------------------------
};


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

  Panel* new_panel(string name, string icon, bool value){
    Panel* panel = new Panel(name, icon, value);
    this->vec_panel.push_back(panel);
    return panel;
  }
  void add_node_panel(utl::type::Node* node){
    vector<Panel*> node_vec_panel = node->get_vec_panel();
    this->vec_panel.insert(vec_panel.end(), node_vec_panel.begin(), node_vec_panel.end());
  }

  inline vector<Panel*> get_vec_panel(){return vec_panel;}

protected:
  utl::type::Node* node_up;
  vector<utl::type::Node*> node_down;
  vector<Panel*> vec_panel;
};

}
