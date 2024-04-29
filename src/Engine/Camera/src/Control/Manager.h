#pragma once

#include <Utility/Specific/Common.h>

namespace sce{class Node;}
namespace dat{class Set;}
namespace cam{class Node;}
namespace cam{class Entity;}


namespace cam{

class Manager
{
public:
  Manager(cam::Node* node_camera);
  ~Manager();

public:
  //Main function
  void create_camera();
  void reset();

  inline cam::Entity* get_camera(int i){return vec_camera[i];}
  inline cam::Entity* get_current_camera(){return current_camera;}

private:
  dat::Set* sce_set;
  sce::Node* node_scene;
  vector<cam::Entity*> vec_camera;
  cam::Entity* current_camera;

  int camera_ID;
};

}
