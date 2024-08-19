#pragma once

#include <Utility/Base/Class/Panel.h>
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

  inline std::vector<utl::gui::Panel*> get_vec_panel(){return vec_panel;}

protected:
  static std::vector<utl::gui::Panel*> vec_panel;
};

}
