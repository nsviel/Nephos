#pragma once

#include <Utility/Specific/Common.h>

namespace sce{class Node;}
namespace dat{class Database;}
namespace dat{class Set;}
namespace ope::attribut{class Location;}
namespace ope{class Operation;}


namespace dat::gui{

class Entity
{
public:
  //Constructor / Destructor
  Entity(sce::Node* node_scene, bool* show_window);
  ~Entity();

  //Main function
  void run_panel();
  void design_panel();
  void close_panel();

  //Sub functions
  void entity_title(utl::type::Entity* entity);
  void entity_button(utl::type::Entity* entity);
  void entity_parameter(utl::type::Entity* entity);

  //Parameter
  void entity_info(utl::type::Entity* entity);
  void data_info(utl::type::Entity* entity);
  void pose_info(utl::type::Entity* entity);

  //Primitive
  void primitive_line(utl::type::Data* data);
  void primitive_point(utl::type::Data* data);
  void primitive_triangle(utl::type::Data* data);

  inline void set_entity(utl::type::Entity* entity){this->entity = entity;}

private:
  ope::attribut::Location* ope_location;
  ope::Operation* ope_operation;
  dat::Database* sce_database;
  dat::Set* sce_set;

  utl::type::Entity* entity;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
