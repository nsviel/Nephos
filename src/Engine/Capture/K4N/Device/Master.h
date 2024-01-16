#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Base/Entity/Struct_entity.h>

class Engine;

namespace k4n{
class Device;


class Master : public entity::Entity
{
public:
  //Constructor / Destructor
  Master(Engine* engine);
  ~Master();

public:
  //Main function

  //Entity function
  void update_entity();
  void remove_entity();
  void reset_entity();
  void visibility_entity(bool value);

public:
  Engine* engine;

  list<k4n::Device*> list_device;
};

}
