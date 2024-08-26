#pragma once


namespace vld::structure{

struct Data{
  //---------------------------

  std::vector<dat::base::Set*> vec_set;
  dat::base::Set* current_set = nullptr;

  std::shared_ptr<dat::base::Object> object = nullptr;
  int current_frame_ID = 0;

  //---------------------------
};

}
