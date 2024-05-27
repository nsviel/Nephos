#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::base{class Exporter;}
namespace dat::base{class Entity;}


namespace ldr::io{

enum Mode{
  ASCII = 0,
  BINARY = 1,
};

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader);
  ~Exporter();

public:
  //Main functions
  void export_entity(dat::base::Entity* entity, std::string path);

  //Exporter function
  void insert_exporter(ldr::base::Exporter* exporter);
  bool is_format_supported(std::string format);
  std::vector<std::string> get_supported_format();

  inline void set_mode(int value){this->mode = value;}

private:
  std::vector<ldr::base::Exporter*> vec_exporter;
  int mode = ldr::io::BINARY;
};

}
