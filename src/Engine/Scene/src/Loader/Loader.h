#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::scene{class Entity;}
namespace eng::scene{class Database;}
namespace eng::scene{class Format;}
namespace eng::scene{class Node;}
namespace eng::scene{class Parameter;}
namespace eng::scene{class Set;}


namespace eng::scene{

class Loader
{
public:
  //Constructor / Destructor
  Loader(eng::scene::Node* node_scene);
  ~Loader();

public:
  //Main functions
  utl::type::Set* load_data(std::string path);
  utl::type::Set* load_data(utl::file::Entity* entity);

  //Data function
  utl::type::Set* load_object(utl::file::Data* data);
  utl::type::Set* load_set(utl::file::Data* data);

  //Subfunction
  bool check_file_path(std::string path);
  utl::entity::Object* create_object(utl::file::Data* data);

private:
  eng::Node* node_engine;
  eng::scene::Format* sce_format;
  eng::scene::Entity* sce_entity;
  eng::scene::Database* sce_database;
  eng::scene::Parameter* sce_param;
  eng::scene::Set* sce_set;
};

}
