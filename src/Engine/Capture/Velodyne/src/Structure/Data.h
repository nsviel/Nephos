#pragma once


namespace vld::structure{

struct Data{
  //---------------------------

  vector<utl::type::Set*> vec_set;
  utl::type::Set* current_set = nullptr;

  //---------------------------
};

}
