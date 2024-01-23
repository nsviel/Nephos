#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace gui::element{

class Git
{
public:
  //Constructor / Destructor
  Git();
  ~Git();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void draw_information();
  void draw_branches();

private:
  util::element::Git* git;
};

}
