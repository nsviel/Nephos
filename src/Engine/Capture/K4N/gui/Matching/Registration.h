#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class K4N;}


namespace k4n::gui{

class Registration
{
public:
  //Constructor / Destructor
  Registration(k4n::Node* node_k4n);
  ~Registration();

public:
  //Main function
  void draw_registration(k4n::dev::Sensor* sensor);

  //Subfunction


private:
  k4n::structure::K4N* k4n_struct;
};

}
