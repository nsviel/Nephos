#pragma once

#include <Utility/Base/GUI/Panel.h>
#include <vector>
#include <string>


namespace utl::base{

class Node
{
public:
  Node();
  ~Node();

public:
  //Main function
  virtual void init(){}
  virtual void loop(){}
  virtual void gui(){}
  virtual void reset(){}
  virtual void clean(){}
  virtual void wait(){}
  virtual void config(){}

  utl::gui::Panel* add_panel(std::string name, std::string icon, bool value){
    //---------------------------

    utl::gui::Panel* panel = new utl::gui::Panel(name, icon, value);
    this->vec_panel.push_back(panel);

    //---------------------------
    return panel;
  }
  void add_node_panel(utl::base::Node* node){
    //---------------------------

    std::vector<utl::gui::Panel*> node_vec_panel = node->get_vec_panel();
    this->vec_panel.insert(vec_panel.end(), node_vec_panel.begin(), node_vec_panel.end());

    //---------------------------
  }

  inline std::vector<utl::gui::Panel*> get_vec_panel(){return vec_panel;}

protected:
  std::vector<utl::gui::Panel*> vec_panel;
};

}
