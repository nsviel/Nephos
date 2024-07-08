#pragma once

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}


namespace k4n::gui{

class Registration
{
public:
  //Constructor / Destructor
  Registration(k4n::Node* node_k4n);
  ~Registration();

public:
  //Main function
  void draw_registration(k4n::base::Sensor* sensor);

  //Subfunction


private:

};

}
