#pragma once

#include <Engine/Data/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Operation/Namespace.h>

class GUI;
class Panel;


namespace gui::rnd::data{

class Entity
{
public:
  //Constructor / Destructor
  Entity(GUI* gui, bool* show_window);
  ~Entity();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void entity_title(eng::data::Entity* entity);
  void entity_button(eng::data::Entity* entity);
  void entity_parameter(eng::data::Entity* entity);

  //Primitive size
  void entity_line(eng::data::Object* object);
  void entity_point(eng::data::Object* object);

  inline void set_entity(eng::data::Entity* entity){this->entity = entity;}

private:
  Panel* gui_render_panel;
  eng::ope::Attribut* ope_attribut;
  eng::ope::Operation* ope_operation;
  eng::scene::Scene* sce_scene;
  eng::scene::Operation* sce_operation;

  eng::data::Entity* entity;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
