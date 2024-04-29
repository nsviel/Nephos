#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Base/Media/File.h>
#include <Utility/Base/Type/Entity.h>
#include <Utility/Base/Type/Set.h>

namespace utl::entity{class Object;}


namespace utl::type{

struct Importer{
  //---------------------------

  virtual utl::File* import(utl::Path path){return nullptr;}
  virtual void insert(utl::type::Entity* entity){}
  virtual void insert(utl::type::Set* set){}

  utl::file::Data* data = nullptr;
  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
