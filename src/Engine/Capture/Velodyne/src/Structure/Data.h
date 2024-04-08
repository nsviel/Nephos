#pragma once


namespace vld::structure{

struct Data{
  //---------------------------

  vector<utl::type::Set*> vec_set;
  vector<utl::entity::Object*> vec_object;
  utl::type::Set* current_set = nullptr;
  int num_object = 5;

  //---------------------------
};

}
