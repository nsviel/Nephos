#pragma once


namespace velodyne::structure{

struct Data{
  //---------------------------

  vector<utl::type::Set*> vec_set;
  utl::type::Set* current_set = nullptr;

  //---------------------------
};

}
