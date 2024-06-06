#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}


namespace dyn::cloud{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(dyn::Node* node_dynamic);
  ~Glyph();

public:
  //Main function
  void init();

private:
  dyn::Structure* dyn_struct;
};

}
