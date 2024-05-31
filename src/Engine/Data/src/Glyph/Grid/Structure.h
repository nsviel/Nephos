#pragma once


namespace dat::glyph::grid{

struct Structure{
  //---------------------------

  virtual void construct(int nb_cell){}
  int nb_cell;

  //---------------------------
};

}
