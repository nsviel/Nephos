#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::base{class Data;}


namespace ope{

class Triangulation
{
public:
  // Constructor / Destructor
  Triangulation();
  ~Triangulation();

public:
  //Main function
  void make_triangulation(utl::base::Data* data);

private:

};

}
