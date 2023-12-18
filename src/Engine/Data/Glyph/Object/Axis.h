#pragma once

#include "../Base/Glyph_source.h"


namespace glyph::object{

class Axis : public Glyph_source
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  void create_axis_scene();
  void create_axis_circle(float circleRadius);
  eng::structure::Glyph* create_axis_subset(eng::structure::Object* object);
  void update_axis_subset(eng::structure::Object* object, eng::structure::Glyph* glyph);

  inline eng::structure::Glyph* get_axis_scene(){return axis_scene;}
  inline eng::structure::Glyph* get_axis_circle(){return axis_circle;}
  inline bool* get_axis_subset_visibility(){return &is_visible;}

private:
  eng::structure::Glyph* axis_scene;
  eng::structure::Glyph* axis_circle;

  bool is_visible;
};

}
