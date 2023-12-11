#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Utility/UTL_specific/common.h>

namespace eng::data{
class Node;


class Database
{
public:
  //Constructor / Destructor
  Database(eng::data::Node* eng_data);
  ~Database();

public:
  inline list<eng::structure::Set*>* get_list_data(){return list_data;}
  inline list<eng::structure::Set*>* get_list_data_glyph(){return list_glyph;}

private:
  int ID_obj;

  list<eng::structure::Set*>* list_data;
  list<eng::structure::Set*>* list_glyph;
};

}
