#pragma once

#include <Utility/Specific/common.h>


namespace ope{

class Triangulation
{
public:
  // Constructor / Destructor
  Triangulation();
  ~Triangulation();

public:
  //Main function
  void make_triangulation(utl::type::Data* data);
  
private:

};

}
