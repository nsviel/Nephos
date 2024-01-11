#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;


namespace eng::camera{

class Manager
{
public:
  Manager(Engine* engine);
  ~Manager();

public:
  //Main function
  void create_camera();

  inline eng::data::Camera* get_camera(int i){return vec_camera[i];}

private:
  vector<eng::data::Camera*> vec_camera;
};

}
