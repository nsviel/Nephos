#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Node;}
namespace dat{class Database;}
namespace dat{class Set;}
namespace ope::attribut{class Location;}
namespace ope{class Operation;}
namespace dat::base{class Entity;}


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
  void data_info(dat::base::Entity* entity);
  void pose_info(dat::base::Entity* entity);

  //Primitive
  void primitive_line(utl::type::Data* data);
  void primitive_point(utl::type::Data* data);
  void primitive_triangle(utl::type::Data* data);

  inline void set_entity(dat::base::Entity* entity){this->entity = entity;}

private:
  ope::attribut::Location* ope_location;
  ope::Operation* ope_operation;
  dat::Database* dat_database;
  dat::Set* dat_set;

  dat::base::Entity* entity;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
