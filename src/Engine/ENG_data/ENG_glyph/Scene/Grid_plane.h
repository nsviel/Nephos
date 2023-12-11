#pragma once

#include "../Base/Glyph_source.h"


class Grid_plane : public Glyph_source
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

  inline data::Glyph* get_grid(){return grid;}
  inline data::Glyph* get_grid_sub(){return grid_sub;}
  inline data::Glyph* get_grid_plane(){return grid_plane;}
  inline vec4* get_grid_color(){return &grid_color;}

private:
  data::Glyph* grid;
  data::Glyph* grid_sub;
  data::Glyph* grid_plane;
  vec4 grid_color;
  vec4 grid_sub_color;
  int nb_cell;
};
