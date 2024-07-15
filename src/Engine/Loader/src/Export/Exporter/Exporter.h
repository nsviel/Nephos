#pragma once

#include <Loader/src/Export/Structure/Exporter.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::exporter{class Operation;}
namespace ldr::base{class Exporter;}
namespace ldr::base{class Recorder;}
namespace dat::base{class Entity;}


namespace ldr::io{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader);
  ~Exporter();

public:
  //Main function
  void export_entity(dat::base::Entity* entity, std::string path);

  //Subfunction
  void init_path();
  void export_with_encoding(ldr::exporter::Base* exporter, dat::base::Entity* entity, std::string path);
  void insert_exporter(ldr::exporter::Base* exporter);
  void update_current_path(utl::base::Element* element);
  bool is_format_supported(std::string format);
  bool is_current_config(dat::base::Entity* entity);
  bool is_recording(utl::base::Element* element);
  std::vector<std::string> get_supported_format();
  std::vector<ldr::exporter::Encoding> get_supported_encoding(std::string format);

private:
  ldr::Structure* ldr_struct;
  ldr::exporter::Operation* ldr_operation;

  std::vector<ldr::exporter::Base*> vec_exporter;
};

}
