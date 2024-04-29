#pragma once

#include <Utility/Specific/Common.h>

namespace eng::scene{class Node;}
namespace eng::scene{class Set;}
namespace cam{class Node;}
namespace cam{class Camera;}


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

  inline cam::Camera* get_camera(int i){return vec_camera[i];}
  inline cam::Camera* get_current_camera(){return current_camera;}

private:
  eng::scene::Set* sce_set;
  eng::scene::Node* node_scene;
  vector<cam::Camera*> vec_camera;
  cam::Camera* current_camera;

  int camera_ID;
};

}
