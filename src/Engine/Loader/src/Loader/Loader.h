#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace sce{class Entity;}
namespace sce{class Database;}
namespace ldr{class Format;}
namespace sce{class Node;}
namespace sce{class Set;}


namespace ldr{

class Loader
{
public:
  //Constructor / Destructor
  Loader(sce::Node* node_scene);
  ~Loader();

public:
  //Main functions
  utl::type::Data* load_data(string path);
  utl::type::Set* load_dataset(utl::Path file_path);
  utl::entity::Object* load_object(utl::Path file_path);

  //Subfunction
  bool check_file_path(std::string path);
  utl::entity::Object* create_object(utl::file::Data* file_data);
  utl::type::Data* create_data(utl::file::Data* file_data);

private:
  eng::Node* node_engine;
  ldr::Format* sce_format;
  sce::Entity* sce_entity;
  sce::Database* sce_database;
  sce::Set* sce_set;
};

}
