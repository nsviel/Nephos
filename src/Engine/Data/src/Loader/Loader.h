#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Engine;}
namespace eng::scene{class Scene;}
namespace eng::scene{class Format;}
namespace eng::scene{class Node;}


namespace eng::scene{

class Loader
{
public:
  //Constructor / Destructor
  Loader(eng::scene::Node* sce_node);
  ~Loader();

public:
  //Main functions
  utl::type::Entity* load_entity(std::string path);

  //Subfunctions
  utl::entity::Object* load_object(string path);
  bool is_format_supported(string format);

private:
  eng::Engine* engine;
  eng::scene::Format* sce_format;
  eng::scene::Scene* sce_scene;

  vector<string> supported_format;
  std::string path_current_dir;
};

}
