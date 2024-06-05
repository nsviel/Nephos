#pragma once

#include <Loader/src/Base/Exporter.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::base{class Exporter;}
namespace dat::base{class Entity;}


namespace ldr::io{

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

  //Subfunction
  std::vector<std::string> get_supported_format();
  std::vector<int> get_supported_encoding(std::string format);

  inline void set_recording(int value){this->recording = value;}

private:
  std::vector<ldr::base::Exporter*> vec_exporter;
  int recording = ldr::io::BINARY;
};

}
