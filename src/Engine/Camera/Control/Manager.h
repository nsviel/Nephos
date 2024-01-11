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

private:
  vector<eng::data::Camera*> vec_camera;
};

}
