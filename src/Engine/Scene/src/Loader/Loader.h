#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace scene{class Entity;}
namespace scene{class Database;}
namespace scene{class Format;}
namespace scene{class Node;}
namespace scene{class Parameter;}
namespace scene{class Set;}


namespace scene{

class Loader
{
public:
  //Constructor / Destructor
  Loader(scene::Node* node_scene);
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
  scene::Format* sce_format;
  scene::Entity* sce_entity;
  scene::Database* sce_database;
  scene::Parameter* sce_param;
  scene::Set* sce_set;
};

}
