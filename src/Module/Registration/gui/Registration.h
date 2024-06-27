#pragma once

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}


namespace k4n::gui{

class Registration
{
public:
  //Constructor / Destructor
  Registration(k4n::Node* node_k4n);
  ~Registration();

public:
  //Main function
  void draw_registration(k4n::structure::Sensor* sensor);

  //Subfunction


private:

};

}
