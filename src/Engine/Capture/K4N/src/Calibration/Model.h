#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace ope::attribut{class Fitting;}


namespace k4n::processing{

class Model
{
public:
  //Constructor / Destructor
  Model(k4n::Node* node_k4n);
  ~Model();

public:
  //Main function


private:
  ope::attribut::Fitting* ope_fitting;
};

}
