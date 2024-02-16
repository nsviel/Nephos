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
  utl::type::Entity* load_entity(std::string path);

  //Subfunctions
  utl::entity::Object* load_object(std::string path);

private:
  eng::Node* engine;
  eng::scene::Format* sce_format;
  eng::scene::Scene* sce_scene;
  eng::scene::Parameter* sce_param;
};

}
