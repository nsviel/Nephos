#pragma once

#include <Utility/Specific/common.h>

class Engine;
namespace eng::cam{class Node;}


namespace eng::cam{

class Manager
{
public:
  Manager(eng::cam::Node* cam_node);
  ~Manager();

public:
  //Main function
  void create_camera();
  void reset();

  inline utl::entity::Camera* get_camera(int i){return vec_camera[i];}
  inline utl::entity::Camera* get_current_camera(){return current_camera;}

private:
  Engine* engine;
  vector<utl::entity::Camera*> vec_camera;
  utl::entity::Camera* current_camera;

  int camera_ID;
};

}
