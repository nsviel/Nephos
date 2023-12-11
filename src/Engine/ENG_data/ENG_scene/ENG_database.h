#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/ENG_data/Namespace.h>
#include <Utility/UTL_specific/common.h>


class ENG_database
{
public:
  //Constructor / Destructor
  ENG_database(eng::data::ENG_data* eng_data);
  ~ENG_database();

public:
  inline list<eng::structure::Set*>* get_list_data(){return list_data;}
  inline list<eng::structure::Set*>* get_list_data_glyph(){return list_glyph;}

private:
  int ID_obj;

  list<eng::structure::Set*>* list_data;
  list<eng::structure::Set*>* list_glyph;
};
