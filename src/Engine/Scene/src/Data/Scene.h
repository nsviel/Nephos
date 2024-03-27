#pragma once

#include <Utility/Specific/Common.h>

namespace eng::scene{class Node;}
namespace eng::scene{class Loader;}


namespace eng::scene{

class Scene
{
public:
  //Constructor / Destructor
  Scene(eng::scene::Node* node_scene);
  ~Scene();

public:
  //Main function
  void init();

private:
  eng::scene::Loader* sce_loader;
};

}
