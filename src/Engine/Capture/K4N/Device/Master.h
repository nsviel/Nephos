#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>

#include <Utility/Specific/common.h>
#include <Utility/Base/Entity/Struct_entity.h>

class Engine;

namespace k4n::dev{
class Sensor;


class Master : public utl::base::Set, public k4n::dev::Device
{
public:
  //Constructor / Destructor
  Master();//Engine* engine);
  ~Master();

public:
  //Main function
  void add_sensor(k4n::dev::Sensor* sensor);

  //Player function
  void set_play();
  void set_pause(bool value);
  void set_desired_timestamp(float value);
  void set_stop();
  void set_restart();
  void set_record();

  inline std::list<entity::Entity*> get_list_entity(){return list<entity::Entity*>(list_sensor.begin(), list_sensor.end());}

public:
  list<k4n::dev::Sensor*> list_sensor;

private:
//  Engine* engine;
};

}
