#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::base{class Data;}


namespace ope{

class Meshlet
{
public:
  // Constructor / Destructor
  Meshlet();
  ~Meshlet();

public:
  //Main function
  void compute(utl::base::Data& data);

private:

};

}
