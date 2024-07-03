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

  //Subfunction
  utl::gui::Panel* add_panel(std::string name, std::string icon, bool value);
  void add_node_panel(utl::base::Node* node);

  inline std::vector<utl::gui::Panel*> get_vec_panel(){return vec_panel;}
  inline std::vector<utl::gui::Panel*> get_vec_panel_shared(){return vec_panel_shared;}

protected:
  std::vector<utl::gui::Panel*> vec_panel;
  static std::vector<utl::gui::Panel*> vec_panel_shared;
};

}
