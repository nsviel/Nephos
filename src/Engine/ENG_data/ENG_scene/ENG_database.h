#ifndef ENG_DATABASE_H
#define ENG_DATABASE_H

#include <ELE_specific/common.h>

class ENG_data;


class ENG_database
{
public:
  //Constructor / Destructor
  ENG_database(ENG_data* eng_data);
  ~ENG_database();

public:
  inline list<Set*>* get_list_data(){return list_data;}
  inline list<Set*>* get_list_data_glyph(){return list_glyph;}

private:
  int ID_obj;

  list<Set*>* list_data;
  list<Set*>* list_glyph;
};

#endif
