#pragma once

#include <string>

namespace eng{class Node;}
namespace ldr{class Format;}
namespace ldr{class Node;}
namespace dat{class Entity;}
namespace dat{class Graph;}
namespace dat{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Object;}
namespace utl::media{class Path;}
namespace utl::base{class Data;}
namespace utl::file{class Data;}


namespace ldr{

class Importer
{
public:
  //Constructor / Destructor
  Importer(ldr::Node* node_loader);
  ~Importer();

public:
  //Main functions
  utl::base::Data* load_data(std::string path);
  dat::base::Set* load_dataset(utl::media::Path file_path);
  dat::base::Object* load_object(utl::media::Path file_path);

  //Subfunction
  bool check_file_path(std::string path);
  dat::base::Object* create_object(utl::file::Data* file_data);
  utl::base::Data* create_data(utl::file::Data* file_data);

private:
  eng::Node* node_engine;
  ldr::Format* ldr_format;
  dat::Entity* dat_entity;
  dat::Graph* dat_graph;
  dat::Set* dat_set;
};

}
