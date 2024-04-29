#pragma once

#include <Utility/Specific/Common.h>

namespace eng::scene{class Node;}
namespace eng::scene{class Set;}
namespace cam{class Node;}
namespace utl::entity{class Camera;}


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

  inline utl::entity::Camera* get_camera(int i){return vec_camera[i];}
  inline utl::entity::Camera* get_current_camera(){return current_camera;}

private:
  eng::scene::Set* sce_set;
  eng::scene::Node* node_scene;
  vector<utl::entity::Camera*> vec_camera;
  utl::entity::Camera* current_camera;

  int camera_ID;
};

}
