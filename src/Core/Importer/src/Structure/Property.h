#pragma once

#include <Importer/src/Structure/Enum.h>


namespace io::imp{

struct Property{

  Property(){}
  Property(io::imp::Field field, io::imp::Type type = io::imp::FLOAT32, int size = 0){
    this->field = field;
    this->type = type;
    this->size = size;
  }

  io::imp::Field field;
  io::imp::Type type;
  int size = 0;
};

}
