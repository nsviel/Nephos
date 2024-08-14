#pragma once

#include <IO/src/Import/Structure/Enum.h>


namespace io::importer{

struct Property{

  Property(){}
  Property(io::importer::Field field, io::importer::Type type = io::importer::FLOAT32, int size = 0){
    this->field = field;
    this->type = type;
    this->size = size;
  }

  io::importer::Field field;
  io::importer::Type type;
  int size = 0;
};

}
