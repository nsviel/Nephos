#pragma once

#include <Engine/Base/Source.h>


namespace glyph::world{

class Grid_plane : public glyph::base::Source
{
public:
  //Constructor / Destructor
  Grid_plane();
  ~Grid_plane();

public:
  void create_grid();
  void create_grid_sub();
  void create_grid_plane();

  void update_grid(int value);
  void update_grid_sub(int value);
  void update_grid_plane(int value);

  inline eng::structure::Glyph* get_grid(){return grid;}
  inline eng::structure::Glyph* get_grid_sub(){return grid_sub;}
  inline eng::structure::Glyph* get_grid_plane(){return grid_plane;}
  inline vec4* get_grid_color(){return &grid_color;}

private:
  eng::structure::Glyph* grid;
  eng::structure::Glyph* grid_sub;
  eng::structure::Glyph* grid_plane;
  vec4 grid_color;
  vec4 grid_sub_color;
  int nb_cell;
};

}
