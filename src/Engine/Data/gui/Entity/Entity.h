#pragma once

#include <string>

namespace dat{class Node;}
namespace dat::graph{class Selection;}
namespace dat::element{class Set;}
namespace dat::element{class Entity;}
namespace dat::base{class Entity;}
namespace ope::attribut{class Location;}
namespace ope{class Operation;}
namespace utl::base{class Data;}


namespace dat::gui{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::Node* node_data, bool* show_window);
  ~Entity();

  //Main function
  void run_panel();
  void design_panel();
  void close_panel();

  //Sub functions
  void entity_title(dat::base::Entity* entity);
  void entity_button(dat::base::Entity* entity);
  void entity_parameter(dat::base::Entity* entity);

  //Parameter
  void entity_info(dat::base::Entity* entity);
  void entity_data(dat::base::Entity* entity);
  void entity_pose(dat::base::Entity* entity);

  //Primitive
  void entity_typology(dat::base::Entity* entity);
  void topology_line(utl::base::Data* data);
  void topology_point(utl::base::Data* data);
  void topology_triangle(utl::base::Data* data);

  inline void set_entity(dat::base::Entity* entity){this->entity = entity;}

private:
  ope::attribut::Location* ope_location;
  ope::Operation* ope_operation;
  dat::graph::Selection* dat_selection;
  dat::element::Set* dat_set;
  dat::element::Entity* dat_entity;

  dat::base::Entity* entity;
  std::string panel_name;
  bool* panel_show;;
  int item_width;
};

}
