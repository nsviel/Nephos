#pragma once

namespace utl::element{class Git;}


namespace utl::element::gui{

class Git
{
public:
  //Constructor / Destructor
  Git();
  ~Git();

public:
  //Main function
  void design_panel();

  //Subfunction
  void draw_information();
  void draw_branches();

private:
  utl::element::Git* git;
};

}
