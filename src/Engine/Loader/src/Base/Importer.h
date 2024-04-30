#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Base/Media/File.h>
#include <Data/src/Base/Entity.h>
#include <Data/src/Base/Set.h>

namespace dat::base{class Object;}


namespace ldr::base{

struct Importer{
  //---------------------------

  virtual utl::File* import(utl::Path path){return nullptr;}
  virtual void insert(dat::base::Entity* entity){}
  virtual void insert(dat::base::Set* set){}

  utl::file::Data* data = nullptr;
  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
