#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Base/Entity/Struct_entity.h>

class Engine;

namespace k4n::dev{
class Sensor;


class Master : public entity::Entity, public k4n::dev::Device
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
  list<k4n::dev::Sensor*> list_sensor;

private:
  Engine* engine;
};

}
