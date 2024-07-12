#pragma once

namespace dat::base{class Entity;}
namespace utl::base{class Data;}


namespace dat::gui::entity{

class Topology
{
public:
  //Constructor / Destructor
  Topology();
  ~Topology();

public:
  //Main function
  void entity_typology(dat::base::Entity* entity);

  //Subfunction
  void topology_line(utl::base::Data* data);
  void topology_point(utl::base::Data* data);
  void topology_triangle(utl::base::Data* data);

private:

};

}
