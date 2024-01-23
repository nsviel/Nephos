#pragma once

#include <Engine/Data/Namespace.h>

#include <Utility/Specific/common.h>
#include <Engine/Operation/src/Namespace.h>

class Panel;


namespace gui::rnd::data{

class Entity
{
public:
  //Constructor / Destructor
  Entity(Engine* engine, bool* show_window);
  ~Entity();

  //Main function
  void run_panel();
  void design_panel();
  void close_panel();

  //Sub functions
  void entity_title(utl::type::Entity* entity);
  void entity_button(utl::type::Entity* entity);
  void entity_parameter(utl::type::Entity* entity);

  //Primitive size
  void data_line(utl::type::Data* data);
  void data_point(utl::type::Data* data);

  inline void set_entity(utl::type::Entity* entity){this->entity = entity;}

private:
  Panel* gui_render_panel;
  eng::ope::Attribut* ope_attribut;
  eng::ope::Operation* ope_operation;
  eng::scene::Scene* sce_scene;

  utl::type::Entity* entity;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
