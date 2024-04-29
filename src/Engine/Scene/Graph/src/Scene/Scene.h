#pragma once

#include <Utility/Specific/Common.h>

namespace scene{class Node;}
namespace scene{class Loader;}
namespace utl::type{class Selection;}


namespace scene{

class Scene
{
public:
  //Constructor / Destructor
  Scene(scene::Node* node_scene);
  ~Scene();

public:
  //Main function
  void init();

private:
  scene::Loader* sce_loader;
  utl::type::Selection* selection = nullptr;
};

}
