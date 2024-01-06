#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::grid{

class Grid_sub : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Grid_sub();
  ~Grid_sub();

public:
  void create_grid();
  void create_grid_sub();
  void create_grid_plane();

  void update_grid(int value);
  void update_grid_sub(int value);
  void update_grid_plane(int value);

  inline eng::data::Object* get_grid(){return grid;}
  inline eng::data::Object* get_grid_sub(){return grid_sub;}
  inline eng::data::Object* get_grid_plane(){return grid_plane;}
  inline vec4* get_grid_color(){return &grid_color;}

private:
  eng::data::Object* grid;
  eng::data::Object* grid_sub;
  eng::data::Object* grid_plane;
  vec4 grid_color;
  vec4 grid_sub_color;
  int nb_cell;
};

}
