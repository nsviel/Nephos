#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::scene{class Scene;}
namespace eng::scene{class Format;}
namespace eng::scene{class Node;}
namespace eng::scene{class Parameter;}


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

  //Subfunctions
  bool check_file_path(std::string path);
  utl::type::Set* load_object(utl::file::Data* data);
  utl::type::Set* load_set(utl::file::Data* data);

private:
  eng::Node* node_engine;
  eng::scene::Format* sce_format;
  eng::scene::Scene* sce_scene;
  eng::scene::Parameter* sce_param;
};

}
