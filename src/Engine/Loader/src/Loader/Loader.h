#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace dat{class Entity;}
namespace dat{class Database;}
namespace ldr{class Format;}
namespace ldr{class Node;}
namespace dat{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Object;}


namespace ldr{

class Loader
{
public:
  //Constructor / Destructor
  Loader(ldr::Node* node_loader);
  ~Loader();

public:
  //Main functions
  utl::type::Data* load_data(std::string path);
  dat::base::Set* load_dataset(utl::media::Path file_path);
  dat::base::Object* load_object(utl::media::Path file_path);

  //Subfunction
  bool check_file_path(std::string path);
  dat::base::Object* create_object(utl::file::Data* file_data);
  utl::type::Data* create_data(utl::file::Data* file_data);

private:
  eng::Node* node_engine;
  ldr::Format* ldr_format;
  dat::Entity* dat_entity;
  dat::Database* dat_database;
  dat::Set* dat_set;
};

}
